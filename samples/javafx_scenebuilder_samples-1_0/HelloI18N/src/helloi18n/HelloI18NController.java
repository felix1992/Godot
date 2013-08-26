/*
 * Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
 */
package helloi18n;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;

/**
 * Controller class of the HelloI18N sample.
 */
public class HelloI18NController implements Initializable {

    @FXML
    Button button;

    private ResourceBundle resources;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
    this.resources = rb;

        if (button != null) {
            button.setOnAction(new EventHandler<ActionEvent>() {

                @Override
                public void handle(ActionEvent event) {
                    System.out.println(resources.getString("button.printed.message"));
                }
            });
        }
    }
}
