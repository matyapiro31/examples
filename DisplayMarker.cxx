/****************************************************************************************

   Copyright (C) 2014 Autodesk, Inc.
   All rights reserved.

   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

#include <fbxsdk.h>

#include "DisplayCommon.h"

void DisplayMarker(FbxNode* pNode)
{
    FbxMarker* lMarker = (FbxMarker*)pNode->GetNodeAttribute();
    FbxString     lString;

    DisplayString("Marker Name: ", (char *) pNode->GetName());
    DisplayMetaDataConnections(lMarker);

    // Type
    lString = "    Marker Type: ";
    switch (lMarker->GetType())
    {
    case FbxMarker::eStandard:    lString += "Standard";    break;
    case FbxMarker::eOptical:     lString += "Optical";     break;
    case FbxMarker::eEffectorIK: lString += "IK Effector"; break;
    case FbxMarker::eEffectorFK: lString += "FK Effector"; break;
    }
    DisplayString(lString.Buffer());

    // Look
    lString = "    Marker Look: ";
    switch (lMarker->Look.Get())
    {
    default:
      break;
    case FbxMarker::eCube:         lString += "Cube";        break;
    case FbxMarker::eHardCross:   lString += "Hard Cross";  break;
    case FbxMarker::eLightCross:  lString += "Light Cross"; break;
    case FbxMarker::eSphere:       lString += "Sphere";      break;
    }
    DisplayString(lString.Buffer());

    // Size
    lString = FbxString("    Size: ") + FbxString(lMarker->Size.Get());
    DisplayString(lString.Buffer());

    // Color
    FbxDouble3 c = lMarker->Color.Get();
    FbxColor color(c[0], c[1], c[2]);
    DisplayColor("    Color: ", color);

    // IKPivot
    Display3DVector("    IKPivot: ", lMarker->IKPivot.Get());
}

// Example of getting FK/IK data from Node and setting it to the FbxControlSet class.
FbxControlSet ExampleControlSet(FbxNode* pNode)
{
	FbxMarker* lMarker = (FbxMarker*)pNode->GetNodeAttribute();
	FbxCharacter* lkFbxCharacter;
	FbxControlSet lKFbxControlSet;
	FbxEffector* lkFbxEffector=new FbxEffector();
	FbxControlSetLink* lkFbxControlSetLink=new FbxControlSetLink();
	int NodeId,NodeSubId;
	int CharacterLinkType;
	
	// Get Type of pNode and Set Node.
	switch (lMarker ->GetType())
	{
		case FbxMarker::eEffectorIK:
			pNode->GetCharacterLink(0,&lkFbxCharacter,&CharacterLinkType,&NodeId,&NodeSubId);
			lFbxControlSet.SetEffector((EEffectorNodeId)NodeId,lkFbxEffector);
			break;
		case FbcMarker::eEffectorFK:
			pNode->GetCharacterLink(0,&lkFbxCharacter,&CharacterLinkType,&NodeId,&NodeSubId);
			lFbxControlSet.SetControlSetLink((ECharacterNodeId)NodeId,lkFbxControlSetLink)
			break;
		default	:
			break;
	}
	
	//If you want to make the part visible, set it true, else false.
	lkFbxEffector.mShow=true;//IK
	lkFbxControlSetLink.mShow=true;//FK
	
	return lkControlSet;
}
