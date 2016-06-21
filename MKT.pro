#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T13:36:52
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = MKT
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    Tokenizer/Token.cpp \
    Tokenizer/TokenFactory.cpp \
    Tokenizer/TokenStream.cpp \
    Parser/Parser.cpp \
    Nodes/CompositeNode.cpp \
    Nodes/Operate.cpp \
    Nodes/Int2DoubleConversion.cpp \
    Nodes/IntNumber.cpp \
    Nodes/DoubleNumber.cpp \
    Nodes/Declaration.cpp \
    Nodes/Assignment.cpp \
    Nodes/Return.cpp \
    Nodes/Program.cpp \
    Nodes/Method.cpp \
    Visitors/GenerateCode.cpp \
    Nodes/Argument.cpp \
    Nodes/PrintCommand.cpp \
    Nodes/FunctionCall.cpp \
    Nodes/Variable.cpp \
    Nodes/IFnode.cpp \
    Nodes/WhileNode.cpp

HEADERS += \
    Tokenizer/Token.hpp \
    Tokenizer/TokenFactory.hpp \
    Tokenizer/TokenStream.hpp \
    Parser/Parser.hpp \
    Visitors/IVisitor.hpp \
    Nodes/INode.hpp \
    Nodes/CompositeNode.hpp \
    Nodes/Operate.hpp \
    Nodes/Int2DoubleConversion.hpp \
    Nodes/IntNumber.hpp \
    Nodes/DoubleNumber.hpp \
    Nodes/Declaration.hpp \
    Nodes/Assignment.hpp \
    Nodes/Return.hpp \
    Nodes/Program.hpp \
    Nodes/Method.hpp \
    Visitors/GenerateCode.hpp \
    Nodes/Argument.hpp \
    Nodes/PrintCommand.hpp \
    Nodes/FunctionCall.hpp \
    Nodes/Variable.hpp \
    Nodes/IFnode.hpp \
    Nodes/WhileNode.hpp
