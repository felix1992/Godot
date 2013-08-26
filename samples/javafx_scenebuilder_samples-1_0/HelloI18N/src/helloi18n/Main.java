/*
 * Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
 */
package helloi18n;

import java.util.Locale;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

public class Main extends Application {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Application.launch(Main.class, (java.lang.String[])null);
    }

    @Override
    public void start(Stage primaryStage) {
        try {
            // This line to resolve keys against Bundle.properties
            ResourceBundle i18nBundle = ResourceBundle.getBundle("helloi18n.Bundle", new Locale("en", "US"));
            // This line to resolve keys against Bundle_fr_FR.properties
//            ResourceBundle i18nBundle = ResourceBundle.getBundle("helloi18n.Bundle", new Locale("fr", "FR"));
            AnchorPane page = (AnchorPane) FXMLLoader.load(Main.class.getResource("HelloI18N.fxml"), i18nBundle);
            Scene scene = new Scene(page);
            primaryStage.setScene(scene);
            primaryStage.setTitle(i18nBundle.getString("application.title"));
            primaryStage.show();
        } catch (Exception ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
