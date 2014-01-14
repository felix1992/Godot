#!/bin/bash
export XFCE_PATH="/home/jpreiss/work/xfce/deploy"
export PKG_CONFIG_PATH="$XFCE_PATH/lib/pkgconfig:$PKG_CONFIG_PATH"
export CFLAGS="-O2 -pipe -Wno-deprecated-declarations"
export XFCE_BRANCH="master"
#export XFCE_BRANCH="xfce-4.10"
export PATH=$XFCE_PATH/bin:$PATH
export LD_LIBRARY_PATH=$XFCE_PATH/lib:$LD_LIBRARY_PATH

#declare -a XFCE_MODULES=("xfce4-docs")
declare -a XFCE_MODULES=(
"xfce4-dev-tools" "libxfce4util" "xfconf" "libxfce4ui" "garcon" "exo" 
"xfce4-panel"
"xfdesktop" "xfwm4" 
"xfce4-appfinder"
##"xfce4-session"
"xfce4-settings" 
"thunar"
##"thunar-desktop-plugin"
"thunar-volman"
"tumbler"
#"xfce4-docs"
)

declare -a XFCE_APPS=(
"xfce4-screenshooter"
"xfce4-taskmanager" "xfce4-terminal" 
"orage" 
"parole"
"ristretto" "xfbib" "mousepad"
"xfce4-dict" "xfce4-profile-manager"
)

declare -a XFCE_PLUGINS=(
"xfce4-battery-plugin"
"xfce4-clipman-plugin"
"xfce4-xkb-plugin"
"xfce4-weather-plugin"
"xfce4-indicator-plugin"
"xfce4-mailwatch-plugin"
"xfce4-eyes-plugin"
"xfce4-cpufreq-plugin"
"xfce4-cpugraph-plugin"
"xfce4-datetime-plugin"
"xfce4-taskbar-plugin"
)

declare -a XFCE_ART=(
"xfce4-artwork"
"xfce4-icon-theme"
"xfwm4-themes"
)

declare -a XFCE_ADDONS=(
"xfdashboard-0.0.1-alpha_20131224"
"xfce4-builder"
)

declare -a DEPENDENCIES=("libtool" "automake" "libglib2.0-dev"
#libxfce4util
"intltool" "gtk-doc-tools"
#xfconf
"libdbus-1-dev" "libdbus-glib-1-dev"
#libxfce4ui
"libx11-dev" "libgtk-3-dev"
##"libgtk2.0-dev"
#xfce4-panel
"libwnck-dev"
#xfce4-docs
"gnome-doc-utils"
#thunar-volman
"libgudev-1.0-dev"
#xfce4-screenshooter
"libsoup2.4-dev"
#xfce4-terminal
"libvte-dev"
#parole
"libgstreamer1.0-dev"
#ristretto
"libexif-dev"
#mousepad
"libgtksourceview2.0-dev"
#xfce-clipman-plugin
"libxtst-dev"
#xfce4-xkb-plugin
"libxklavier-dev" "librsvg2-dev"
#xfce-indicator-plugin
"libindicator3-dev"
#xfce-mailwatch-plugin
"libgcrypt11-dev"
#xfdashboard
#warning, big "libclutter-1.0-dev"
)

autogen=false
cleanup=false
aptcalled=false
buildmodules=true
buildapps=true
buildplugins=true
buildart=true
buildaddons=true

if [ ! -d $XFCE_PATH ]; then
    mkdir $XFCE_PATH
fi

function color_red {
    echo -e '\E[0;31m'"\033[1m$1\033[0m"    # Red
}

function color_green {
    echo -e '\E[0;32m'"\033[1m$1\033[0m"  # Green
}

function color_off {
    tput sgr0
}

function checkout {
    local part=$1
    local module=$2
    pushd . > /dev/null

    if [ -d $module ]; then
        cd $module
        git pull 
    else
        git clone git://git.xfce.org/$part/$module
        cd $module
        git checkout -b devel origin/$XFCE_BRANCH
    fi

    popd > /dev/null
}

function call_apt {
    color_green "Probably there are some packages missing. Calling apt to install..."

    local packages=""
    for dep in ${DEPENDENCIES[@]}
    do
        packages="$packages $dep"
    done

    sudo apt-get --yes install $packages >> build.log   
    #sudo apt-get --yes install $dep    

    aptcalled=true
}


function call_autogen {
    local module=$1

    color_green "Calling autogen for $module"
    local params="--prefix=$XFCE_PATH --enable-maintainer-mode"
    
    if [ "$module" == "xfce4-docs" ]; then
        params="$params --enable-gen-doc"
#    elif [ "$module" == "libxfce4util" ]; then
#        params="$params --disable-debug --enable-gtk3"
#    elif [ "$module" == "libxfce4ui" ]; then
#        params="$params --disable-debug --enable-gtk3"
    else
        params="$params --disable-debug --enable-gtk3"
    fi

    ./autogen.sh $params
    result=$?
    if [ ! $result -eq 0 ];
    then
        if $aptcalled
        then
            color_red "Error calling autogen for $module"
            exit -2
        fi
        call_apt
        call_autogen $module
    fi
}

function build {
    local module=$1

    color_green "Calling build for $module"
    pushd .

    cd $module

    if $autogen 
    then
        call_autogen $module
    elif [ ! -f "config.status" ]; then
        call_autogen $module
    fi

    make
    result=$?
    if [ ! $result -eq 0 ];
    then
        color_red "Error while calling make"
        exit -1
    fi

    if [ "$module" != "xfce4-docs" ]; then
        make install 
        result=$?
        if [ ! $result -eq 0 ];
        then
            color_red "Error while calling install"
            exit -1
        fi
    fi

    popd
}



while getopts "acdmprx?" optname
do
    case "$optname" in
        "a")
            echo "Calling autogen.sh"
            autogen=true
            ;;
        "c")
            cleanup=true
            ;;
        "d")
            buildaddons=false
            ;;
        "m")
            buildmodules=false
            ;;
        "p")
            buildplugins=false
            ;;
        "r")
            buildart=false
            ;;
        "x")
            buildapps=false
            ;;
        "?")
            echo "Build XFCE from scratch. Available parameters:"
            echo "-a  call autogen.sh even if config.status already exists"
            echo "-c  remove all outputs and directories"
            echo "-d  do not build the addons"
            echo "-m  do not build the modules"
            echo "-p  do not build the plugins"
            echo "-r  do not build the art"
            echo "-x  do not build the applications"
            exit 2
            ;;
        ":")
            echo "No argument value for option $OPTARG"
            ;;
        *)
            # Should not occur
            echo "Unknown error while processing options"
            exit 1
            ;;
    esac
done

if $cleanup 
then
    echo "Cleaning up..."
    for module in ${XFCE_MODULES[@]}
    do
        if [ -d "$module" ]; then
            echo "Removing $module"
            rm -rf $module
        fi
    done
    for app in ${XFCE_APPS[@]}
    do
        if [ -d "$app" ]; then
            echo "Removing $app"
            rm -rf $app
        fi
    done
    for plugin in ${XFCE_PLUGINS[@]}
    do
        if [ -d "$plugin" ]; then
            echo "Removing $plugin"
            rm -rf $plugin
        fi
    done
    for art in ${XFCE_ART[@]}
    do
        if [ -d "$art" ]; then
            echo "Removing $art"
            rm -rf $art
        fi
    done
    echo "Removing $XFCE_PATH"
    rm -rf $XFCE_PATH
    echo "ready"
    exit 0
fi

if $buildmodules
then
    for module in ${XFCE_MODULES[@]}
    do
        color_green "Processing $module"
        
        checkout "xfce" $module
        build $module 
    done
fi

if $buildapps
then
    for app in ${XFCE_APPS[@]}
    do
        color_green "Processing $app"
    
        checkout "apps" $app
        build $app 
    done
fi

if $buildplugins
then
    for plugin in ${XFCE_PLUGINS[@]}
    do
        color_green "Processing $plugin"
    
        checkout "panel-plugins" $plugin
        build $plugin 
    done
fi

if $buildart
then
    for art in ${XFCE_ART[@]}
    do
        color_green "Processing $art"
    
        checkout "art" $art
        build $art 
    done
fi

if $buildaddons
then
    for addon in ${XFCE_ADDONS[@]}
    do
        color_green "Processing $addon"
   
        if [ -d "$addon" ]; then
            build $addon 
        else
            color_red "$addon not found"
        fi
    done
fi


