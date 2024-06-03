cmake_minimum_required(VERSION 3.10)

project(nexus VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(nexus 
	STATIC 
	"Source/Collections/HashFunctions.cpp"
	"Source/Patterns/Factory.cpp"
	"Source/Utility/Bounds2D.cpp"
	"Source/Utility/Maths.cpp"
	"Source/Utility/Point2D.cpp"
  "Source/Patterns/FactoryObject.cpp")

target_include_directories(nexus 
	PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/tinyxml
)

add_subdirectory(tinyxml)