// Some copyright should be here...

using UnrealBuildTool;
using System.IO;
using System;

public class C2I_Socket : ModuleRules
{
	public C2I_Socket(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;


        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"C2I_Socket/Private",
				
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Networking",
				"Sockets",
				
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",

				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        LoadGoogleProtocolBuffers(Target);

    }

    public bool LoadGoogleProtocolBuffers(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64))
        {
            isLibrarySupported = true;

            string LibrariesPath = Path.Combine(ThirdPartyPath, "libprotobuf", "lib");

            Console.WriteLine("... LibrariesPath -> " + LibrariesPath);
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libprotobuf" + ".lib"));
        }

        if (isLibrarySupported)
        {
            string IncludePath = Path.Combine(ThirdPartyPath, "libprotobuf", "include");

            Console.WriteLine("... IncludePath -> " + IncludePath);
            PrivateIncludePaths.Add(IncludePath);
        }

        PublicDefinitions.Add(string.Format("WITH_GPB_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }
    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }
}
