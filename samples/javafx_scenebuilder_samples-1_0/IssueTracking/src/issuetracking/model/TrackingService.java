/*
 * Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
 */
package issuetracking.model;

import javafx.collections.ObservableList;
import issuetracking.model.Issue.IssuePriority;
import issuetracking.model.Issue.IssueStatus;

public interface TrackingService {

    public ObservableList<String> getIssueIds(String projectName);
    public ObservableList<String> getProjectNames();
    public ObservableIssue getIssue(String tickectId);
    public ObservableIssue createIssueFor(String projectName);
    public void deleteIssue(String issueId);
    public void saveIssue(String issueId,
            IssueStatus status, IssuePriority priority,
            String synopsis, String description);
}
