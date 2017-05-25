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
#ifndef _MESSAGEPOPUP_HH_
#define _MESSAGEPOPUP_HH_

#include <gazebo/common/Plugin.hh>
#include <gazebo/gui/GuiPlugin.hh>
#ifndef Q_MOC_RUN  // See: https://bugreports.qt-project.org/browse/QTBUG-22829
# include <gazebo/transport/transport.hh>
# include <gazebo/gui/gui.hh>
#endif

namespace gazebo
{
    class GAZEBO_VISIBLE MessagePopup : public GUIPlugin
    {
      Q_OBJECT

		/// \brief Subscriber callback input parameter type
		typedef const boost::shared_ptr<const gazebo::msgs::Any> AnyPtr;	
	
      /// \brief Constructor
      public: MessagePopup();

      /// \brief Destructor
      public: virtual ~MessagePopup();

      /// \brief Node used to establish communication with gzserver.
      private: transport::NodePtr node;
		
		/// \brief Subscriber to messages.
   	private: transport::SubscriberPtr subscribe;

		/// \brief Subscriber callback function	
		protected: void ReceiveMessage(AnyPtr &_msg);
	
		public slots: 
			/// \brief Create popup function
			void Create(const char *message);
		
		signals: 
			/// \brief signal that create popup function 
			void Popup(const char *message);	
    };
}
#endif

