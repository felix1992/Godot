/*
 * Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
 */
package login.security;

import java.util.HashMap;
import java.util.Map;

public class Authenticator {
    private static final Map<String, String> USERS = new HashMap<String, String>();
    static {
        USERS.put("demo", "demo");
    }
    public static boolean validate(String user, String password){
        String validUserPassword = USERS.get(user);
        return validUserPassword != null && validUserPassword.equals(password);
    }
}
