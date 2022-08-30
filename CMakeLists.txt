cmake_minimum_required(VERSION 3.16.3)
project(KNNClassifier)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Server
        Server/Commands/ClassifyCommand.cpp
        Server/Commands/ClassifyCommand.hpp
        Server/Commands/Command.cpp
        Server/Commands/Command.hpp
        Server/Commands/ConfusionMatrixCommand.cpp
        Server/Commands/ConfusionMatrixCommand.hpp
        Server/Commands/DisplayCommand.cpp
        Server/Commands/DisplayCommand.hpp
        Server/Commands/DownloadCommand.cpp
        Server/Commands/DownloadCommand.hpp
        Server/Commands/SettingsCommand.cpp
        Server/Commands/SettingsCommand.hpp
        Server/Commands/UploadCommand.cpp
        Server/Commands/UploadCommand.hpp
        Server/IOServices/DefaultIO.cpp
        Server/IOServices/DefaultIO.hpp
        Server/IOServices/SocketIO.cpp
        Server/IOServices/SocketIO.hpp
        Server/IOServices/StandardIO.cpp
        Server/IOServices/StandardIO.hpp
        Server/Classifier/Classifier.cpp
        Server/Classifier/Classifier.hpp
        Server/Classifier/Item.cpp
        Server/Classifier/Item.hpp
        Server/Classifier/NPoints.cpp
        Server/Classifier/NPoints.hpp
        Server/Classifier/srcDistances/DistanceCalc.cpp
        Server/Classifier/srcDistances/DistanceCalc.hpp
        Server/Classifier/srcDistances/distCalculators/ChebyshevDistance.cpp
        Server/Classifier/srcDistances/distCalculators/ChebyshevDistance.hpp
        Server/Classifier/srcDistances/distCalculators/EuclideanDistance.cpp
        Server/Classifier/srcDistances/distCalculators/EuclideanDistance.hpp
        Server/Classifier/srcDistances/distCalculators/ManhattanDistance.cpp
        Server/Classifier/srcDistances/distCalculators/ManhattanDistance.hpp
        Server/CLI.hpp
        Server/CLI.cpp Server/ServerCode/ServerProcess.cpp Server/ServerCode/ServerProcess.hpp Server/toDeleteLater/ThreadPool.cpp Server/toDeleteLater/ThreadPool.hpp Server/toDeleteLater/WorkingThread.cpp Server/toDeleteLater/WorkingThread.hpp)