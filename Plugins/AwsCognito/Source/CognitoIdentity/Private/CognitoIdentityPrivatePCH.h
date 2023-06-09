/**
* Copyright (C) 2017-2023 eelDev AB
*
* Official Documentation: https://docs.aws.amazon.com/cognitoidentity/latest/APIReference/API_Operations.html
*/

#include <CoreMinimal.h>
#include <Modules/ModuleInterface.h>
#include <Interfaces/IPluginManager.h>
#include <Misc/MessageDialog.h>
#include <Misc/Paths.h>
#include <HAL/FileManager.h>
#include <Modules/ModuleManager.h>
#include <GenericPlatform/GenericPlatformOutputDevices.h>
#include <GenericPlatform/GenericPlatformProcess.h>
#include <Async/TaskGraphInterfaces.h>
#include <CoreGlobals.h>
#include <Misc/ConfigCacheIni.h>

#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#endif

#include <map>
#include <string>
#include <memory>
#include <sstream>

#if !DISABLE_COGNITO
THIRD_PARTY_INCLUDES_START
#include <aws/core/Aws.h>
#include <aws/core/utils/logging/AWSLogging.h>
#include <aws/core/utils/logging/ConsoleLogSystem.h>
#include <aws/core/utils/logging/DefaultLogSystem.h>
#include <aws/core/utils/logging/FormattedLogSystem.h>
#include <aws/core/client/DefaultRetryStrategy.h>
#include <aws/core/auth/AWSCredentials.h>
#include <aws/cognito-identity/model/GetIdRequest.h>
#include <aws/cognito-identity/model/GetCredentialsForIdentityRequest.h>
#include <aws/cognito-identity/model/CreateIdentityPoolRequest.h>
#include <aws/cognito-identity/model/DeleteIdentitiesRequest.h>
#include <aws/cognito-identity/model/DeleteIdentityPoolRequest.h>
#include <aws/cognito-identity/model/DescribeIdentityPoolRequest.h>
#include <aws/cognito-identity/model/DescribeIdentityRequest.h>
#include <aws/cognito-identity/model/GetIdentityPoolRolesRequest.h>
#include <aws/cognito-identity/model/GetOpenIdTokenForDeveloperIdentityRequest.h>
#include <aws/cognito-identity/model/GetOpenIdTokenRequest.h>
#include <aws/cognito-identity/model/ListIdentitiesRequest.h>
#include <aws/cognito-identity/model/ListIdentityPoolsRequest.h>
#include <aws/cognito-identity/model/ListTagsForResourceRequest.h>
#include <aws/cognito-identity/model/LookupDeveloperIdentityRequest.h>
#include <aws/cognito-identity/model/MergeDeveloperIdentitiesRequest.h>
#include <aws/cognito-identity/model/SetIdentityPoolRolesRequest.h>
#include <aws/cognito-identity/model/TagResourceRequest.h>
#include <aws/cognito-identity/model/UnlinkIdentityRequest.h>
#include <aws/cognito-identity/model/UntagResourceRequest.h>
#include <aws/cognito-identity/model/UpdateIdentityPoolRequest.h>
#include <aws/cognito-identity/model/CreateIdentityPoolResult.h>
#include <aws/cognito-identity/model/DeleteIdentitiesResult.h>
#include <aws/cognito-identity/model/DescribeIdentityPoolResult.h>
#include <aws/cognito-identity/model/DescribeIdentityResult.h>
#include <aws/cognito-identity/model/GetCredentialsForIdentityResult.h>
#include <aws/cognito-identity/model/GetIdentityPoolRolesResult.h>
#include <aws/cognito-identity/model/GetOpenIdTokenForDeveloperIdentityResult.h>
#include <aws/cognito-identity/model/GetOpenIdTokenResult.h>
#include <aws/cognito-identity/model/ListIdentitiesResult.h>
#include <aws/cognito-identity/model/ListIdentityPoolsResult.h>
#include <aws/cognito-identity/model/ListTagsForResourceResult.h>
#include <aws/cognito-identity/model/LookupDeveloperIdentityResult.h>
#include <aws/cognito-identity/model/MergeDeveloperIdentitiesResult.h>
#include <aws/cognito-identity/model/TagResourceResult.h>
#include <aws/cognito-identity/model/UntagResourceResult.h>
#include <aws/cognito-identity/model/UpdateIdentityPoolResult.h>
#include <aws/cognito-identity/model/UnlinkDeveloperIdentityRequest.h>
#include <aws/cognito-identity/model/RoleMapping.h>
THIRD_PARTY_INCLUDES_END
#endif