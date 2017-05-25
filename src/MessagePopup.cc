/*
 * Copyright (C) 2014 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#include <sstream>
#include <gazebo/msgs/msgs.hh>
#include "MessagePopup.hh"
#include <iostream>

#include <QApplication>
#include <QMessageBox>

using namespace gazebo;

// Register this plugin with the simulator
GZ_REGISTER_GUI_PLUGIN(MessagePopup)


MessagePopup::MessagePopup() : GUIPlugin()
{
  // Position and resize this widget
  this->move(0, 0);
  this->resize(0, 0);

  //connect signal to the Create popup function
  QObject::connect(this, SIGNAL(Popup(const char *)),
                     this, SLOT(Create(const char *))); 	

  // Create a node for transportation
  this->node = transport::NodePtr(new transport::Node());
  this->node->Init("default");
  this->subscribe = this->node->Subscribe("~/popup/message",
      &MessagePopup::ReceiveMessage, this);
}


MessagePopup::~MessagePopup() 
{
}


void MessagePopup::ReceiveMessage(AnyPtr &_msg)
{
	//emit the signal
	emit Popup(_msg->string_value().c_str());
}


void MessagePopup::Create(const char *message)
{
	QMessageBox* msgBox = new QMessageBox();
	msgBox->setWindowTitle("Gazebo");
	msgBox->setText(QString::fromUtf8(message));
	//msgBox->setIconPixmap(QPixmap("/images/trophy.png"));
	msgBox->setIcon(QMessageBox::Information);
	msgBox->setWindowFlags(Qt::WindowStaysOnTopHint);
	msgBox->show();
}

