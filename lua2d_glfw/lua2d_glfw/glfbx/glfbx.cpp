//
//  glfbx.cpp
//  lua2d_glfw
//
//  Created by chenbingfeng on 15/5/13.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#include "glfbx.h"
#include <iostream>
#include <string>

#include <fbxsdk.h>
#include <stdio.h>

static int numTabs = 0;

void printTabs(){
    for (int i = 0; i < numTabs; i++) {
        std::cout << "\t";
    }
}

FbxString getAttributeTypeName(FbxNodeAttribute::EType type)
{
    switch(type) {
        case FbxNodeAttribute::eUnknown: return "unidentified";
        case FbxNodeAttribute::eNull: return "null";
        case FbxNodeAttribute::eMarker: return "marker";
        case FbxNodeAttribute::eSkeleton: return "skeleton";
        case FbxNodeAttribute::eMesh: return "mesh";
        case FbxNodeAttribute::eNurbs: return "nurbs";
        case FbxNodeAttribute::ePatch: return "patch";
        case FbxNodeAttribute::eCamera: return "camera";
        case FbxNodeAttribute::eCameraStereo: return "stereo";
        case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
        case FbxNodeAttribute::eLight: return "light";
        case FbxNodeAttribute::eOpticalReference: return "optical reference";
        case FbxNodeAttribute::eOpticalMarker: return "marker";
        case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
        case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
        case FbxNodeAttribute::eBoundary: return "boundary";
        case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
        case FbxNodeAttribute::eShape: return "shape";
        case FbxNodeAttribute::eLODGroup: return "lodgroup";
        case FbxNodeAttribute::eSubDiv: return "subdiv";
        default: return "unknown";
    }
}

void printAttribute(FbxNodeAttribute* attribute) {
    if (!attribute) return;

    FbxString typeName = getAttributeTypeName(attribute->GetAttributeType());
    FbxString attrName = attribute->GetName();

    printTabs();
    std::cout << "<attribute type=' "<< typeName.Buffer() << "' name='" << attrName.Buffer() << "'/>" << std::endl;
}

void printNode(FbxNode* node)
{
    printTabs();

    const char * nodeName = node->GetName();
    FbxDouble3 translation = node->LclTranslation.Get();
    FbxDouble3 rotation = node->LclTranslation.Get();
    FbxDouble3 scaling = node->LclScaling.Get();

    printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
           nodeName,
           translation[0], translation[1], translation[2],
           rotation[0], rotation[1], rotation[2],
           scaling[0], scaling[1], scaling[2]
           );
    numTabs++;

    for (int i = 0; i < node->GetNodeAttributeCount(); i++) {
        printAttribute(node->GetNodeAttributeByIndex(i));
    }

    for (int i = 0; i < node->GetChildCount(); i++) {
        printNode(node->GetChild(i));
    }

    numTabs--;
    printTabs();
    printf("</node>\n");

}

void glFbxMain()
{
    std::cout << "hello glfbx!" << std::endl;

    // get the scene
    const char* fileName = "cubeman.fbx";

    FbxManager* sdkManager = FbxManager::Create();

    FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
    sdkManager->SetIOSettings(ios);

    FbxImporter*  importer = FbxImporter::Create(sdkManager, "");

    if (!importer->Initialize(fileName, -1, sdkManager->GetIOSettings())) {
        std::cerr << "Call to FbxImport::Initialize() failed, " << importer->GetStatus().GetErrorString() << std::endl;
        exit(-1);
    }

    FbxScene* scene = FbxScene::Create(sdkManager, "myScene");

    importer->Import(scene);

    importer->Destroy();

    // explore the scene
    FbxNode* rootNode = scene->GetRootNode();
    if (rootNode) {
        for (int i = 0; i < rootNode->GetChildCount();  i++) {
            printNode(rootNode->GetChild(i));
        }
    }

    sdkManager->Destroy();
}