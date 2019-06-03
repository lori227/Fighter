// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class libprotobuf : ModuleRules
{
    private string LibProtoPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/lib")); }
    }

    private string HeadPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/include/src")); }
    }

    public libprotobuf(ReadOnlyTargetRules Target):base(Target)
	{
        bEnableExceptions = true;
        bEnableShadowVariableWarnings = false;
        bEnableUndefinedIdentifierWarnings = false;
        
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



         switch (Target.Platform)
        {
            case UnrealTargetPlatform.IOS:
                {

                    break;
                }
            case UnrealTargetPlatform.Android:
                {

                    break;
                }
            case UnrealTargetPlatform.Win64:
                {
                    PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
                    PublicAdditionalLibraries.Add(Path.Combine(LibProtoPath, "Win64/libprotobuf.lib"));
                    break;
                }
            case UnrealTargetPlatform.Mac:
                {
                    PublicAdditionalLibraries.Add(Path.Combine(LibProtoPath, "Mac/libprotobuf.a"));
			        break;
                }
            case UnrealTargetPlatform.Linux:
                {
                    break;
                }
        }
    }
}
