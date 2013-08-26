/*
 * Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
 */
package issuetracking;

import issuetracking.model.Issue;
import issuetracking.model.Issue.IssuePriority;
import issuetracking.model.Issue.IssueStatus;
import issuetracking.model.ObservableIssue;
import issuetracking.model.TrackingService;
import issuetracking.model.TrackingServiceStub;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.*;
import javafx.animation.FadeTransition;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ListChangeListener;
import javafx.collections.ListChangeListener.Change;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.event.EventType;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TableColumn.CellDataFeatures;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Region;
import javafx.util.Callback;
import javafx.util.Duration;

public class IssueTrackingController implements Initializable {

    @FXML
    Button newIssue;
    @FXML
    Button deleteIssue;
    @FXML
    Button saveIssue;
    @FXML
    TableView<ObservableIssue> table;
    @FXML
    TableColumn<ObservableIssue, String> colName;
    @FXML
    TableColumn<ObservableIssue, String> colDate;
    @FXML
    TableColumn<ObservableIssue, IssuePriority> colPriority;
    @FXML
    TableColumn<ObservableIssue, IssueStatus> colStatus;
    @FXML
    TableColumn<ObservableIssue, String> colSynopsis;
    @FXML
    ListView<String> list;
    @FXML
    TextField synopsis;
    private String displayedBugId; // the id of the bug displayed in the details section.
    private String displayedBugProject; // the name of the project of the bug displayed in the details section.
    @FXML
    Label displayedIssueLabel; // the displayedIssueLabel will contain a concatenation
                               // of the project name and the bug id.
    @FXML
    AnchorPane details;
    @FXML
    Region titleLine;
    @FXML
    TextArea descriptionValue;
    @FXML
    TextField activityField;
    @FXML
    TextField statusValue;
    @FXML
    TextField priorityValue;
    @FXML
    TextField creationTimeValue;
    @FXML
    Label messageBar;
    ObservableList<String> projectsView = FXCollections.observableArrayList();
    TrackingService model = null;
    final ObservableList<ObservableIssue> tableContent = FXCollections.observableArrayList();

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rsrcs) {
        assert activityField != null : "fx:id=\"activityField\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert colDate != null : "fx:id=\"colDate\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert colName != null : "fx:id=\"colName\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert colPriority != null : "fx:id=\"colPriority\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert colStatus != null : "fx:id=\"colStatus\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert colSynopsis != null : "fx:id=\"colSynopsis\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert creationTimeValue != null : "fx:id=\"creationTimeValue\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert deleteIssue != null : "fx:id=\"deleteIssue\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert descriptionValue != null : "fx:id=\"descriptionValue\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert details != null : "fx:id=\"details\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert displayedIssueLabel != null : "fx:id=\"displayedIssueLabel\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert messageBar != null : "fx:id=\"messageBar\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert newIssue != null : "fx:id=\"newIssue\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert priorityValue != null : "fx:id=\"priorityValue\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert saveIssue != null : "fx:id=\"saveIssue\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert statusValue != null : "fx:id=\"statusValue\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert synopsis != null : "fx:id=\"synopsis\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert table != null : "fx:id=\"table\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert titleLine != null : "fx:id=\"titleLine\" was not injected: check your FXML file 'IssueTracking.fxml'.";
        assert list != null : "fx:id=\"list\" was not injected: check your FXML file 'IssueTracking.fxml'.";

        System.out.println(this.getClass().getSimpleName() + ".initialize");
        configureButtons();
        configureDetails();
        configureTable();
        connectToService();
        if (list != null) {
            list.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
            list.getSelectionModel().selectedItemProperty().addListener(projectItemSelected);
            displayedProjectNames.addListener(projectNamesListener);
        }
    }

    /**
     * Called when the NewIssue button is fired.
     *
     * @param event the action event.
     */
    public void newIssueFired(ActionEvent event) {
        final String selectedProject = getSelectedProject();
        if (model != null && selectedProject != null) {
            ObservableIssue issue = model.createIssueFor(selectedProject);
            if (table != null) {
                // Select the newly created issue.
                table.getSelectionModel().clearSelection();
                table.getSelectionModel().select(issue);
            }
            displayMessage("New issue created for " + selectedProject);
        }
    }

    /**
     * Called when the DeleteIssue button is fired.
     *
     * @param event the action event.
     */
    public void deleteIssueFired(ActionEvent event) {
        final String selectedProject = getSelectedProject();
        if (model != null && selectedProject != null && table != null) {
            // We create a copy of the current selection: we can't delete
            //    issue while looping over the live selection, since
            //    deleting selected issues will modify the selection.
            final List<?> selectedIssue = new ArrayList<Object>(table.getSelectionModel().getSelectedItems());
            for (Object o : selectedIssue) {
                if (o instanceof ObservableIssue) {
                    model.deleteIssue(((ObservableIssue) o).getId());
                    displayMessage("Issue deleted: " + ((ObservableIssue) o).getId());
                }
            }
            table.getSelectionModel().clearSelection();
        }
    }

    /**
     * Called when the SaveIssue button is fired.
     *
     * @param event the action event.
     */
    public void saveIssueFired(ActionEvent event) {
        final ObservableIssue ref = getSelectedIssue();
        final Issue edited = new DetailsData();
        SaveState saveState = computeSaveState(edited, ref);
        if (saveState == SaveState.INVALID) {
            displayMessage("Invalid Data: cannot save issue");
        } else if (saveState == SaveState.UNSAVED) {
            model.saveIssue(ref.getId(), edited.getStatus(),
                    edited.getPriority(), edited.getSynopsis(),
                    edited.getDescription());
            displayMessage("Issue saved");
        } else {
            displayMessage("No change needs saving");
        }
        // We refresh the content of the table because synopsis and/or description
        // are likely to have been modified by the user.
        int selectedRowIndex = table.getSelectionModel().getSelectedIndex();
        table.getItems().clear();
        displayedIssues = model.getIssueIds(getSelectedProject());
        for (String id : displayedIssues) {
            final ObservableIssue issue = model.getIssue(id);
            table.getItems().add(issue);
        }
        table.getSelectionModel().select(selectedRowIndex);

        updateSaveIssueButtonState();
    }
    
    FadeTransition messageTransition = null;

    public void displayMessage(String message) {
        if (messageBar != null) {
            if (messageTransition != null) {
                messageTransition.stop();
            } else {
                messageTransition = new FadeTransition(Duration.millis(2000), messageBar);
                messageTransition.setFromValue(1.0);
                messageTransition.setToValue(0.0);
                messageTransition.setDelay(Duration.millis(1000));
                messageTransition.setOnFinished(new EventHandler<ActionEvent>() {

                    @Override
                    public void handle(ActionEvent event) {
                        messageBar.setVisible(false);
                    }
                });
            }
            messageBar.setText(message);
            messageBar.setVisible(true);
            messageBar.setOpacity(1.0);
            messageTransition.playFromStart();
        }
    }

    private void configureButtons() {
        if (newIssue != null) {
            newIssue.setDisable(true);
        }
        if (saveIssue != null) {
            saveIssue.setDisable(true);
        }
        if (deleteIssue != null) {
            deleteIssue.setDisable(true);
        }
    }

    // An observable list of project names obtained from the model.
    // This is a live list, and we will react to its changes by removing
    // and adding project names to/from our list widget.
    private ObservableList<String> displayedProjectNames;
    
    // The list of Issue IDs relevant to the selected project. Can be null
    // if no project is selected. This list is obtained from the model.
    // This is a live list, and we will react to its changes by removing
    // and adding Issue objects to/from our table widget.
    private ObservableList<String> displayedIssues;
    
    // This listener will listen to changes in the displayedProjectNames list,
    // and update our list widget in consequence.
    private final ListChangeListener<String> projectNamesListener = new ListChangeListener<String>() {

        @Override
        public void onChanged(Change<? extends String> c) {
            if (projectsView == null) {
                return;
            }
            while (c.next()) {
                if (c.wasAdded() || c.wasReplaced()) {
                    for (String p : c.getAddedSubList()) {
                        projectsView.add(p);
                    }
                }
                if (c.wasRemoved() || c.wasReplaced()) {
                    for (String p : c.getRemoved()) {
                        projectsView.remove(p);
                    }
                }
            }
            FXCollections.sort(projectsView);
        }
    };
    
    // This listener will listen to changes in the displayedIssues list,
    // and update our table widget in consequence.
    private final ListChangeListener<String> projectIssuesListener = new ListChangeListener<String>() {

        @Override
        public void onChanged(Change<? extends String> c) {
            if (table == null) {
                return;
            }
            while (c.next()) {
                if (c.wasAdded() || c.wasReplaced()) {
                    for (String p : c.getAddedSubList()) {
                        table.getItems().add(model.getIssue(p));
                    }
                }
                if (c.wasRemoved() || c.wasReplaced()) {
                    for (String p : c.getRemoved()) {
                        ObservableIssue removed = null;
                        // Issue already removed:
                        // we can't use model.getIssue(issueId) to get it.
                        // we need to loop over the table content instead.
                        // Then we need to remove it - but outside of the for loop
                        // to avoid ConcurrentModificationExceptions.
                        for (ObservableIssue t : table.getItems()) {
                            if (t.getId().equals(p)) {
                                removed = t;
                                break;
                            }
                        }
                        if (removed != null) {
                            table.getItems().remove(removed);
                        }
                    }
                }
            }
        }
    };

    // Connect to the model, get the project's names list, and listen to
    // its changes. Initializes the list widget with retrieved project names.
    private void connectToService() {
        if (model == null) {
            model = new TrackingServiceStub();
            displayedProjectNames = model.getProjectNames();
        }
        projectsView.clear();
        List<String> sortedProjects = new ArrayList<String>(displayedProjectNames);
        Collections.sort(sortedProjects);
        projectsView.addAll(sortedProjects);
        list.setItems(projectsView);
    }
    
    // This listener listen to changes in the table widget selection and
    // update the DeleteIssue button state accordingly.
    private final ListChangeListener<ObservableIssue> tableSelectionChanged =
            new ListChangeListener<ObservableIssue>() {

                @Override
                public void onChanged(Change<? extends ObservableIssue> c) {
                    updateDeleteIssueButtonState();
                    updateBugDetails();
                    updateSaveIssueButtonState();
                }
            };

    private static String nonNull(String s) {
        return s == null ? "" : s;
    }

    private void updateBugDetails() {
        final ObservableIssue selectedIssue = getSelectedIssue();
        if (details != null && selectedIssue != null) {
            if (displayedIssueLabel != null) {
                displayedBugId = selectedIssue.getId();
                displayedBugProject = selectedIssue.getProjectName();
                displayedIssueLabel.setText( displayedBugId + " / " + displayedBugProject );
            }
            if (synopsis != null) {
                synopsis.setText(nonNull(selectedIssue.getSynopsis()));
            }
            if (statusValue != null) {
                statusValue.setText(selectedIssue.getStatus().toString());
            }
            if (priorityValue != null) {
                priorityValue.setText(selectedIssue.getPriority().toString());
            }
            if (creationTimeValue != null) {
                creationTimeValue.setText(formatDate(selectedIssue.getDate()));
            }
            if (descriptionValue != null) {
                descriptionValue.selectAll();
                descriptionValue.cut();
                descriptionValue.setText(selectedIssue.getDescription());
            }
        } else {
            displayedIssueLabel.setText("");
            displayedBugId = null;
            displayedBugProject = null;
        }
        if (details != null) {
            details.setVisible(selectedIssue != null);
        }
    }

    private boolean isVoid(Object o) {
        if (o instanceof String) {
            return isEmpty((String) o);
        } else {
            return o == null;
        }
    }

    private boolean isEmpty(String s) {
        return s == null || s.trim().isEmpty();
    }

    private boolean equal(Object o1, Object o2) {
        if (isVoid(o1)) {
            return isVoid(o2);
        }
        return o1.equals(o2);
    }

    private static enum SaveState {

        INVALID, UNSAVED, UNCHANGED
    }

    private final class DetailsData implements Issue {

        @Override
        public long getDate() {
            return getSelectedIssue().getDate();
        }

        @Override
        public IssueStatus getStatus() {
            if (statusValue == null || isEmpty(statusValue.getText())) {
                return null;
            }
            return IssueStatus.valueOf(statusValue.getText().trim());
        }

        @Override
        public IssuePriority getPriority() {
            if (priorityValue == null || isEmpty(priorityValue.getText())) {
                return null;
            }
            return IssuePriority.valueOf(priorityValue.getText().trim());
        }

        @Override
        public String getId() {
            if (displayedBugId == null || isEmpty(displayedIssueLabel.getText())) {
                return null;
            }
            return displayedBugId;
        }

        @Override
        public String getProjectName() {
            if (displayedBugProject == null || isEmpty(displayedIssueLabel.getText())) {
                return null;
            }
            return displayedBugProject;
        }

        @Override
        public String getSynopsis() {
            if (synopsis == null || isEmpty(synopsis.getText())) {
                return "";
            }
            return synopsis.getText();
        }

        @Override
        public String getDescription() {
            if (descriptionValue == null || isEmpty(descriptionValue.getText())) {
                return "";
            }
            return descriptionValue.getText();
        }
    }

    private SaveState computeSaveState(Issue edited, Issue issue) {
        try {
            // These fields are not editable - so if they differ they are invalid
            // and we cannot save.
            if (!equal(edited.getDate(), issue.getDate())) {
                return SaveState.INVALID;
            }
            if (!equal(edited.getId(), issue.getId())) {
                return SaveState.INVALID;
            }
            if (!equal(edited.getProjectName(), issue.getProjectName())) {
                return SaveState.INVALID;
            }

            // If these fields differ, the issue needs saving.
            if (!equal(edited.getStatus(), issue.getStatus())) {
                return SaveState.UNSAVED;
            }
            if (!equal(edited.getPriority(), issue.getPriority())) {
                return SaveState.UNSAVED;
            }
            if (!equal(edited.getSynopsis(), issue.getSynopsis())) {
                return SaveState.UNSAVED;
            }
            if (!equal(edited.getDescription(), issue.getDescription())) {
                return SaveState.UNSAVED;
            }
        } catch (Exception x) {
            // If there's an exception, some fields are invalid.
            return SaveState.INVALID;
        }
        // No field is invalid, no field needs saving.
        return SaveState.UNCHANGED;
    }

    private void updateDeleteIssueButtonState() {
        boolean disable = true;
        if (deleteIssue != null && table != null) {
            final boolean nothingSelected = table.getSelectionModel().getSelectedItems().isEmpty();
            disable = nothingSelected;
        }
        if (deleteIssue != null) {
            deleteIssue.setDisable(disable);
        }
    }

    private void updateSaveIssueButtonState() {
        boolean disable = true;
        if (saveIssue != null && table != null) {
            final boolean nothingSelected = table.getSelectionModel().getSelectedItems().isEmpty();
            disable = nothingSelected;
        }
        if (disable == false) {
            disable = computeSaveState(new DetailsData(), getSelectedIssue()) != SaveState.UNSAVED;
        }
        if (saveIssue != null) {
            saveIssue.setDisable(disable);
        }
    }

    private String formatDate(long date) {
        final SimpleDateFormat format = new SimpleDateFormat();
        return format.format(new Date(date));
    }
    
    // Configure the table widget: set up its column, and register the
    // selection changed listener.
    private void configureTable() {
        colName.setCellValueFactory(new PropertyValueFactory<ObservableIssue, String>("id"));
        colDate.setCellValueFactory(new Callback<TableColumn.CellDataFeatures<ObservableIssue, String>, ObservableValue<String>>() {

            @Override
            public ObservableValue<String> call(CellDataFeatures<ObservableIssue, String> param) {
                // The creation date will never change...
                Issue issue = (Issue) param.getValue();
                long creationTime = issue.getDate();
                String date = formatDate(creationTime);
                return new SimpleStringProperty(date);
            }
        });
        colPriority.setCellValueFactory(new PropertyValueFactory<ObservableIssue, IssuePriority>("priority"));
        colStatus.setCellValueFactory(new PropertyValueFactory<ObservableIssue, IssueStatus>("status"));
        colSynopsis.setCellValueFactory(new PropertyValueFactory<ObservableIssue, String>("synopsis"));

        table.setColumnResizePolicy(TableView.CONSTRAINED_RESIZE_POLICY);

        table.setItems(tableContent);
        assert table.getItems() == tableContent;

        final ObservableList<ObservableIssue> tableSelection = table.getSelectionModel().getSelectedItems();

        tableSelection.addListener(tableSelectionChanged);
    }

    /**
     * Return the name of the project currently selected, or null if no project
     * is currently selected.
     *
     */
    public String getSelectedProject() {
        if (model != null && list != null) {
            final ObservableList<String> selectedProjectItem = list.getSelectionModel().getSelectedItems();
            final String selectedProject = selectedProjectItem.get(0);
            return selectedProject;
        }
        return null;
    }

    public ObservableIssue getSelectedIssue() {
        if (model != null && table != null) {
            List<ObservableIssue> selectedIssues = table.getSelectionModel().getSelectedItems();
            if (selectedIssues.size() == 1) {
                final ObservableIssue selectedIssue = selectedIssues.get(0);
                return selectedIssue;
            }
        }
        return null;
    }
    
    /**
     * Listen to changes in the list selection, and updates the table widget and
     * DeleteIssue and NewIssue buttons accordingly.
     */
    private final ChangeListener<String> projectItemSelected = new ChangeListener<String>() {

        @Override
        public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
            projectUnselected(oldValue);
            projectSelected(newValue);
        }
    };

    // Called when a project is unselected.
    private void projectUnselected(String oldProjectName) {
        if (oldProjectName != null) {
            displayedIssues.removeListener(projectIssuesListener);
            displayedIssues = null;
            table.getSelectionModel().clearSelection();
            table.getItems().clear();
            if (newIssue != null) {
                newIssue.setDisable(true);
            }
            if (deleteIssue != null) {
                deleteIssue.setDisable(true);
            }
        }
    }

    // Called when a project is selected.
    private void projectSelected(String newProjectName) {
        if (newProjectName != null) {
            table.getItems().clear();
            displayedIssues = model.getIssueIds(newProjectName);
            for (String id : displayedIssues) {
                final ObservableIssue issue = model.getIssue(id);
                table.getItems().add(issue);
            }
            displayedIssues.addListener(projectIssuesListener);
            if (newIssue != null) {
                newIssue.setDisable(false);
            }
            updateDeleteIssueButtonState();
            updateSaveIssueButtonState();
        }
    }

    private void configureDetails() {
        if (details != null) {
            details.setVisible(false);
        }

        if (details != null) {
            details.addEventFilter(EventType.ROOT, new EventHandler<Event>() {

                @Override
                public void handle(Event event) {
                    if (event.getEventType() == MouseEvent.MOUSE_RELEASED
                            || event.getEventType() == KeyEvent.KEY_RELEASED) {
                        updateSaveIssueButtonState();
                    }
                }
            });
        }
    }
}
