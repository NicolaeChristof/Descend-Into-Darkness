// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DescendIntoDarknessTarget : TargetRules
{
	public DescendIntoDarknessTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("DescendIntoDarkness");
	}
}
