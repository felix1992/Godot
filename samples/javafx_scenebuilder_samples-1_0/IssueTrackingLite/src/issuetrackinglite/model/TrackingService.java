/*
 * Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
 */
package issuetrackinglite.model;

import issuetrackinglite.model.Issue.IssueStatus;
import javafx.collections.ObservableList;

public interface TrackingService {

    public ObservableList<String> getIssueIds(String projectName);
    public ObservableList<String> getProjectNames();
    public ObservableIssue getIssue(String tickectId);
    public ObservableIssue createIssueFor(String projectName);
    public void deleteIssue(String issueId);
    public void saveIssue(String issueId, IssueStatus status,
            String synopsis, String description);
}
