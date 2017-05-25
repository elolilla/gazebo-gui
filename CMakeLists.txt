cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(gazebo-gui)

find_package (Qt4)
find_package(Protobuf REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  gazebo_ros
  control_toolbox
)
find_package(gazebo REQUIRED)

include (${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

catkin_package(
  DEPENDS
    roscpp
    gazebo_ros
    control_toolbox
)

include_directories(SYSTEM ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

QT4_WRAP_CPP(header_time src/TimeWidget.hh)
QT4_WRAP_CPP(header_score src/ScoreWidget.hh)
QT4_WRAP_CPP(header_popup src/MessagePopup.hh)

add_library(message_popup SHARED ${header_popup}
  src/MessagePopup.cc)
target_link_libraries(message_popup ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} 
    ${OGRE_LIBRARIES} 
    ${OGRE-Terrain_LIBRARIES}
    ${QT_LIBRARIES}
    ${PROTOBUF_LIBRARIES})

add_library(time_widget SHARED ${header_time}
  src/TimeWidget.cc)
target_link_libraries(time_widget ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} 
    ${OGRE_LIBRARIES} 
    ${OGRE-Terrain_LIBRARIES}
    ${QT_LIBRARIES}
    ${PROTOBUF_LIBRARIES})

add_library(score_widget SHARED ${header_score}
  src/ScoreWidget.cc)
target_link_libraries(score_widget ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES} 
    ${OGRE_LIBRARIES} 
    ${OGRE-Terrain_LIBRARIES}
    ${QT_LIBRARIES}
    ${PROTOBUF_LIBRARIES})
