/*
 * Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
 */
package issuetrackinglite.model;

public interface Issue {

    public static enum IssueStatus {
        NEW, OPENED, FIXED, CLOSED
    }

    public String getId();
    public String getProjectName();
    public IssueStatus getStatus();
    public String getSynopsis();
    public String getDescription();
}
