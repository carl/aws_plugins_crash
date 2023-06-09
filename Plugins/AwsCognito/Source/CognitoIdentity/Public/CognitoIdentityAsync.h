/**
* Copyright (C) 2017-2023 eelDev AB
*
* Official Documentation: https://docs.aws.amazon.com/cognitoidentity/latest/APIReference/API_Operations.html
*/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIdentityTypes.h"
#include "CognitoPlatformSharedTypes.h"
#include "CognitoIdentityAsync.generated.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityCreateIdentityPool
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreateIdentityPoolCallback, bool, bSuccess, const FCreateIdentityPoolResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityCreateIdentityPool : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCreateIdentityPoolCallback Callback;
public:
	/**
	 * Creates a new identity pool. The identity pool is a store of user identity information that is specific to your AWS account. 
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityCreateIdentityPool* CreateIdentityPool(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FCreateIdentityPoolRequest& Request);
protected:
	FCreateIdentityPoolRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityDeleteIdentities
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDeleteIdentitiesCallback, bool, bSuccess, const FDeleteIdentitiesResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityDeleteIdentities : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeleteIdentitiesCallback Callback;
public:
	/**
	 * Deletes identities from an identity pool. You can specify a list of 1-60 identities that you want to delete.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityDeleteIdentities* DeleteIdentities(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FDeleteIdentitiesRequest& Request);
protected:
	FDeleteIdentitiesRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityDescribeIdentity
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDescribeIdentityCallback, bool, bSuccess, const FDescribeIdentityResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityDescribeIdentity : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDescribeIdentityCallback Callback;
public:
	/**
	 * Returns metadata related to the given identity, including when the identity was created and any associated linked logins.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityDescribeIdentity* DescribeIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FDescribeIdentityRequest& Request);
protected:
	FDescribeIdentityRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityGetId
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetIdCallback, bool, bSuccess, const FGetIdResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityGetId : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetIdCallback Callback;
public:
	/**
	 * Generates (or retrieves) a Cognito ID. Supplying multiple logins will create an implicit linked account.
	 *
	 * This is a public API. You do not need any credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityGetId* GetId(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetIdRequest& Request);
protected:
	FGetIdRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityGetCredentialsForIdentity
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetCredentialsForIdentityCallback, bool, bSuccess, const FGetCredentialsForIdentityResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityGetCredentialsForIdentity : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetCredentialsForIdentityCallback Callback;
public:
	/**
	 * Returns credentials for the provided identity ID. Any provided logins will be validated against supported login providers. If the token is for cognito-identity.amazonaws.com, it will be passed through to AWS Security Token Service with the appropriate role for the token.
	 *
	 * This is a public API. You do not need any credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityGetCredentialsForIdentity* GetCredentialsForIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetCredentialsForIdentityRequest& Request);
protected:
	FGetCredentialsForIdentityRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityGetIdentityPoolRoles
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetIdentityPoolRolesCallback, bool, bSuccess, const FGetIdentityPoolRolesResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityGetIdentityPoolRoles : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetIdentityPoolRolesCallback Callback;
public:
	/**
	 * Gets the roles for an identity pool.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityGetIdentityPoolRoles* GetIdentityPoolRoles(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetIdentityPoolRolesRequest& Request);
protected:
	FGetIdentityPoolRolesRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityGetOpenIdToken
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetOpenIdTokenCallback, bool, bSuccess, const FGetOpenIdTokenResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityGetOpenIdToken : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetOpenIdTokenCallback Callback;
public:
	/**
	 * Gets an OpenID token, using a known Cognito ID. This known Cognito ID is returned by GetId. You can optionally add additional logins for the identity. Supplying multiple logins creates an implicit link.
	 * The OpenID token is valid for 10 minutes.
	 *
	 * This is a public API. You do not need any credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityGetOpenIdToken* GetOpenIdToken(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetOpenIdTokenRequest& Request);
protected:
	FGetOpenIdTokenRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityGetOpenIdTokenForDeveloperIdentity
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetOpenIdTokenForDeveloperIdentityCallback, bool, bSuccess, const FGetOpenIdTokenForDeveloperIdentityResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityGetOpenIdTokenForDeveloperIdentity : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetOpenIdTokenForDeveloperIdentityCallback Callback;
public:
	/**
	 * Registers (or retrieves) a Cognito IdentityId and an OpenID Connect token for a user authenticated by your backend authentication process. Supplying multiple logins will create an implicit linked account. You can only specify one developer provider as part of the Logins map, which is linked to the identity pool. The developer provider is the "domain" by which Cognito will refer to your users.
	 * You can use GetOpenIdTokenForDeveloperIdentity to create a new identity and to link new logins (that is, user credentials issued by a public provider or developer provider) to an existing identity. When you want to create a new identity, the IdentityId should be null. When you want to associate a new login with an existing authenticated/unauthenticated identity, you can do so by providing the existing IdentityId. This API will create the identity in the specified IdentityPoolId.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityGetOpenIdTokenForDeveloperIdentity* GetOpenIdTokenForDeveloperIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FGetOpenIdTokenForDeveloperIdentityRequest& Request);
protected:
	FGetOpenIdTokenForDeveloperIdentityRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityListIdentities
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListIdentitiesCallback, bool, bSuccess, const FListIdentitiesResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityListIdentities : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListIdentitiesCallback Callback;
public:
	/**
	 * Lists the identities in an identity pool.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityListIdentities* ListIdentities(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FListIdentitiesRequest& Request);
protected:
	FListIdentitiesRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityListIdentityPools
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListIdentityPoolsCallback, bool, bSuccess, const FListIdentityPoolsResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityListIdentityPools : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListIdentityPoolsCallback Callback;
public:
	/**
	 * Lists all of the Cognito identity pools registered for your account.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityListIdentityPools* ListIdentityPools(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FListIdentityPoolsRequest& Request);
protected:
	FListIdentityPoolsRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityListTagsForResource
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnListTagsForResourceCallback, bool, bSuccess, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityListTagsForResource : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListTagsForResourceCallback Callback;
public:
	/**
	 * Lists the tags that are assigned to an Amazon Cognito identity pool.
	 * A tag is a label that you can apply to identity pools to categorize and manage them in different ways, such as by purpose, owner, environment, or other criteria.
	 *
	* You can use this action up to 10 times per second, per account.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityListTagsForResource* ListTagsForResource(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FListTagsForResourceRequest& Request);
protected:
	FListTagsForResourceRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityLookupDeveloperIdentity
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLookupDeveloperIdentityCallback, bool, bSuccess, const FLookupDeveloperIdentityResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityLookupDeveloperIdentity : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnLookupDeveloperIdentityCallback Callback;
public:
	/**
	 * Retrieves the IdentityID associated with a DeveloperUserIdentifier or the list of DeveloperUserIdentifier values associated with an IdentityId for an existing identity. Either IdentityID or DeveloperUserIdentifier must not be null. If you supply only one of these values, the other value will be searched in the database and returned as a part of the response. If you supply both, DeveloperUserIdentifier will be matched against IdentityID. If the values are verified against the database, the response returns both values and is the same as the Request. Otherwise a ResourceConflictException is thrown.
	 * LookupDeveloperIdentity is intended for low-throughput control plane operations: for example, to enable customer service to locate an identity ID by username. If you are using it for higher-volume operations such as user authentication, your Requests are likely to be throttled. GetOpenIdTokenForDeveloperIdentity is a better option for higher-volume operations for user authentication.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityLookupDeveloperIdentity* LookupDeveloperIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FLookupDeveloperIdentityRequest& Request);
protected:
	FLookupDeveloperIdentityRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityMergeDeveloperIdentities
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnMergeDeveloperIdentitiesCallback, bool, bSuccess, const FMergeDeveloperIdentitiesResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityMergeDeveloperIdentities : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnMergeDeveloperIdentitiesCallback Callback;
public:
	/**
	 * Merges two users having different IdentityIds, existing in the same identity pool, and identified by the same developer provider. You can use this action to Request that discrete users be merged and identified as a single user in the Cognito environment. Cognito associates the given source user (SourceUserIdentifier) with the IdentityId of the DestinationUserIdentifier. Only developer-authenticated users can be merged. If the users to be merged are associated with the same public provider, but as two different users, an exception will be thrown.
	 * The number of linked logins is limited to 20. So, the number of linked logins for the source user, SourceUserIdentifier, and the destination user, DestinationUserIdentifier, together should not be larger than 20. Otherwise, an exception will be thrown.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityMergeDeveloperIdentities* MergeDeveloperIdentities(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FMergeDeveloperIdentitiesRequest& Request);
protected:
	FMergeDeveloperIdentitiesRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentitySetIdentityPoolRoles
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSetIdentityPoolRolesCallback, bool, bSuccess, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentitySetIdentityPoolRoles : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnSetIdentityPoolRolesCallback Callback;
public:
	/**
	 * Sets the roles for an identity pool. These roles are used when making calls to GetCredentialsForIdentity action.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentitySetIdentityPoolRoles* SetIdentityPoolRoles(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FSetIdentityPoolRolesRequest& Request);
protected:
	FSetIdentityPoolRolesRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityTagResource
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTagResourceCallback, bool, bSuccess, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityTagResource : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnTagResourceCallback Callback;
public:
	/**
	 * Assigns a set of tags to the specified Amazon Cognito identity pool. A tag is a label that you can use to categorize and manage identity pools in different ways, such as by purpose, owner, environment, or other criteria.
	 * Each tag consists of a key and value, both of which you define. A key is a general category for more specific values. For example, if you have two versions of an identity pool, one for testing and another for production, you might assign an Environment tag key to both identity pools. The value of this key might be Test for one identity pool and Production for the other.
	 * Tags are useful for cost tracking and access control. You can activate your tags so that they appear on the Billing and Cost Management console, where you can track the costs associated with your identity pools. In an IAM policy, you can constrain permissions for identity pools based on specific tags or tag values.
	 *
	 * You can use this action up to 5 times per second, per account. An identity pool can have as many as 50 tags.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityTagResource* TagResource(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FTagResourceRequest& Request);
protected:
	FTagResourceRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityUnlinkDeveloperIdentity
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUnlinkDeveloperIdentityCallback, bool, bSuccess, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityUnlinkDeveloperIdentity : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUnlinkDeveloperIdentityCallback Callback;
public:
	/**
	 * Unlinks a DeveloperUserIdentifier from an existing identity. Unlinked developer users will be considered new identities next time they are seen. If, for a given Cognito identity, you remove all federated identities as well as the developer user identifier, the Cognito identity becomes inaccessible.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityUnlinkDeveloperIdentity* UnlinkDeveloperIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FUnlinkDeveloperIdentityRequest& Request);
protected:
	FUnlinkDeveloperIdentityRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityUnlinkIdentity
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUnlinkIdentityCallback, bool, bSuccess, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityUnlinkIdentity : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUnlinkIdentityCallback Callback;
public:
	/**
	 * Unlinks a federated identity from an existing account. Unlinked logins will be considered new identities next time they are seen. Removing the last linked login will make this identity inaccessible.
	 *
	 * This is a public API. You do not need any credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityUnlinkIdentity* UnlinkIdentity(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FUnlinkIdentityRequest& Request);
protected:
	FUnlinkIdentityRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityUntagResource
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUntagResourceCallback, bool, bSuccess, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityUntagResource : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUntagResourceCallback Callback;
public:
	/**
	 * Removes the specified tags from the specified Amazon Cognito identity pool. You can use this action up to 5 times per second, per account
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityUntagResource* UntagResource(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FUntagResourceRequest& Request);
protected:
	FUntagResourceRequest RequestData;
private:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoIdentityUpdateIdentityPool
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateIdentityPoolCallback, bool, bSuccess, const FUpdateIdentityPoolResult&, result, ECognitoIdentityErrors, errorType, const FString&, errorMessage);

UCLASS()
class UCognitoIdentityUpdateIdentityPool : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateIdentityPoolCallback Callback;
public:
	/**
	 * Updates an identity pool.
	 *
	 * You must use AWS Developer credentials to call this API.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito|Identity", BlueprintInternalUseOnly="true"))
	static UCognitoIdentityUpdateIdentityPool* UpdateIdentityPool(UObject* WorldContextObject, UCognitoIdentityPlatform* CognitoPlatform, const FUpdateIdentityPoolRequest& Request);
protected:
	FUpdateIdentityPoolRequest RequestData;
private:
	virtual void Activate() override;
};
