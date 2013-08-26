/*
 * Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
 */
package helloworld;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;

/**
 * Controller class of the HelloWorld sample.
 */
public class HelloWorldController implements Initializable {

    @FXML
    Button button;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rsrcs) {
        if (button != null) {
            button.setOnAction(new EventHandler<ActionEvent>() {

                @Override
                public void handle(ActionEvent event) {
                    System.out.println("Hello World");
                }
            });
        }
    }
}
