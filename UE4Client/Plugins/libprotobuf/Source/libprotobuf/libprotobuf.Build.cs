// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class libprotobuf : ModuleRules
{

    private string LibProtoPathR
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/lib/Release/libprotobuf.lib")); }
    }
    private string LibProtoPathD
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/lib/Debug/libprotobufd.lib")); }
    }
    private string HeadPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/include")); }
    }

    public libprotobuf(ReadOnlyTargetRules Target):base(Target)
	{
       // Type = ModuleType.External;

        PublicIncludePaths.AddRange(
			new string[] {
                HeadPath
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
                "libprotobuf/Private",
                 HeadPath
			}
			);

        PrivatePCHHeaderFile = "Public/libprotobuf.h";
        
        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "HTTP",
                "Json"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            PublicAdditionalLibraries.Add(LibProtoPathR);
        }

        bEnableShadowVariableWarnings = false;
        bEnableUndefinedIdentifierWarnings = false;
        bEnableExceptions = true;

        if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
        {
            //Definitions.Add("_CRT_SECURE_NO_WARNINGS");
            PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
        }
    }
}
