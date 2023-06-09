/**
* Copyright (C) 2017-2023 eelDev AB
*/

#pragma once

#include "CoreMinimal.h"
#include "CognitoTypes.h"
#include "CognitoPlatformSharedTypes.h"
#include "CognitoAsync.generated.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoInitiateAuth
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnInitiateAuthCallback, bool, bSuccess, const FInitiateAuthResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoInitiateAuth : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnInitiateAuthCallback Callback;
public:
	/**
	 * Initiates the authentication flow.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoInitiateAuth* InitiateAuth(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FInitiateAuthRequest& Request);
protected:
	FInitiateAuthRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoSignUp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSignUpCallback, bool, bSuccess, const FSignUpResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoSignUp : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnSignUpCallback Callback;
public:
	/**
	 * Registers the user in the specified user pool and creates a user name, password, and user attributes.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoSignUp* SignUp(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSignUpRequest& Request);
protected:
	FSignUpRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoConfirmSignUp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnConfirmSignUpCallback, bool, bSuccess, const FConfirmSignUpResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoConfirmSignUp : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnConfirmSignUpCallback Callback;
public:
	/**
	 * Confirms registration of a user and handles the existing alias from a previous user.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoConfirmSignUp* ConfirmSignUp(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FConfirmSignUpRequest& Request);
protected:
	FConfirmSignUpRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoForgotPassword
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnForgotPasswordCallback, bool, bSuccess, const FForgotPasswordResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoForgotPassword : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnForgotPasswordCallback Callback;
public:
	/**
	 * Calling this API causes a message to be sent to the end user with a
	 * confirmation code that is required to change the user's password. For the
	 * Username parameter, you can use the username or user alias. 
	 *
	 * The method used to send the confirmation code is sent according to the specified
	 * AccountRecoverySetting. For more information, see 
	 * https://docs.aws.amazon.com/cognito/latest/developerguide/how-to-recover-a-user-account.html
	 * in the Amazon Cognito Developer Guide.
	 *
	 * If neither a verified phone number nor a verified email exists, an
	 * InvalidParameterException is thrown. 
	 *
	 * Queues the Request into a thread executor and triggers associated callback when operation has finished.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoForgotPassword* ForgotPassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FForgotPasswordRequest& Request);
protected:
	FForgotPasswordRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoConfirmForgotPassword
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnConfirmForgotPasswordCallback, bool, bSuccess, const FConfirmForgotPasswordResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoConfirmForgotPassword : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnConfirmForgotPasswordCallback Callback;
public:
	/**
	 * Allows a user to enter a confirmation code to reset a forgotten
	 * password.
	 *
	 * Queues the Request into a thread executor and triggers associated callback when operation has finished.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoConfirmForgotPassword* ConfirmForgotPassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FConfirmForgotPasswordRequest& Request);
protected:
	FConfirmForgotPasswordRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoResendConfirmationCode
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnResendConfirmationCodeCallback, bool, bSuccess, const FResendConfirmationCodeResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoResendConfirmationCode : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnResendConfirmationCodeCallback Callback;
public:
	/**
	 * Resends the confirmation (for confirmation of registration) to a specific
	 * user in the user pool.
	 *
	 * Queues the Request into a thread executor and triggers associated callback when operation has finished.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoResendConfirmationCode* ResendConfirmationCode(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FResendConfirmationCodeRequest& Request);
protected:
	FResendConfirmationCodeRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoRespondToAuthChallenge
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnRespondToAuthChallengeCallback, bool, bSuccess, const FRespondToAuthChallengeResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoRespondToAuthChallenge : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnRespondToAuthChallengeCallback Callback;
public:
	/**
	 * Responds to the authentication challenge
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoRespondToAuthChallenge* RespondToAuthChallenge(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FRespondToAuthChallengeRequest& Request);
protected:
	FRespondToAuthChallengeRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGetUser
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetUserCallback, bool, bSuccess, const FGetUserResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGetUser : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetUserCallback Callback;
public:
	/**
	 * Resends the confirmation (for confirmation of registration) to a specific
	 * user in the user pool.
	 *
	 * Queues the Request into a thread executor and triggers associated callback when operation has finished.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGetUser* GetUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetUserRequest& Request);
protected:
	FGetUserRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAddCustomAttributes
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAddCustomAttributesCallback, bool, bSuccess, const FAddCustomAttributesResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAddCustomAttributes : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAddCustomAttributesCallback Callback;
public:
	/**
	 * Adds additional user attributes to the user pool schema.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAddCustomAttributes* AddCustomAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAddCustomAttributesRequest& Request);
protected:
	FAddCustomAttributesRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminAddUserToGroup
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAdminAddUserToGroupCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminAddUserToGroup : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminAddUserToGroupCallback Callback;
public:
	/**
	 * Adds the specified user to the specified group.
	 * Calling this action requires developer credentials.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminAddUserToGroup* AdminAddUserToGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminAddUserToGroupRequest& Request);
protected:
	FAdminAddUserToGroupRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognito
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminConfirmSignUpCallback, bool, bSuccess, const FAdminConfirmSignUpResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminConfirmSignUp : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminConfirmSignUpCallback Callback;
public:
	/**
	 * Confirms user registration as an admin without using a confirmation code. Works on any user.
	 * Calling this action requires developer credentials.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminConfirmSignUp* AdminConfirmSignUp(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminConfirmSignUpRequest& Request);
protected:
	FAdminConfirmSignUpRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminCreateUser
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminCreateUserCallback, bool, bSuccess, const FAdminCreateUserResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminCreateUser : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminCreateUserCallback Callback;
public:
	/**
	* Creates a new user in the specified user pool.
	* 
	* If MessageAction is not set, the default is to send a welcome message via email or phone (SMS).
	* This message is based on a template that you configured in your call to create or update a user pool. This template includes your custom sign-up instructions and placeholders for user name and temporary password.
	* Alternatively, you can call AdminCreateUser with �SUPPRESS� for the MessageAction parameter, and Amazon Cognito will not send any email.
	* In either case, the user will be in the FORCE_CHANGE_PASSWORD state until they sign in and change their password.
	* 
	* AdminCreateUser requires developer credentials.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminCreateUser* AdminCreateUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminCreateUserRequest& Request);
protected:
	FAdminCreateUserRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminDeleteUser
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAdminDeleteUserCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminDeleteUser : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminDeleteUserCallback Callback;
public:
	/**
	 * Deletes a user as an administrator. Works on any user.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminDeleteUser* AdminDeleteUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminDeleteUserRequest& Request);
protected:
	FAdminDeleteUserRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminDeleteUserAttributes
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminDeleteUserAttributesCallback, bool, bSuccess, const FAdminDeleteUserAttributesResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminDeleteUserAttributes : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminDeleteUserAttributesCallback Callback;
public:
	/**
	 * Deletes the user attributes in a user pool as an administrator. Works on any user.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminDeleteUserAttributes* AdminDeleteUserAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminDeleteUserAttributesRequest& Request);
protected:
	FAdminDeleteUserAttributesRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminDisableProviderForUser
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminDisableProviderForUserCallback, bool, bSuccess, const FAdminDisableProviderForUserResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminDisableProviderForUser : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminDisableProviderForUserCallback Callback;
public:
	/**
	* Disables the user from signing in with the specified external (SAML or social) identity provider. If the user to disable is a Cognito User Pools native username + password user, they are not permitted to use their password to sign-in. If the user to disable is a linked external IdP user, any link between that user and an existing user is removed. The next time the external user (no longer attached to the previously linked DestinationUser) signs in, they must create a new user account. See AdminLinkProviderForUser.
	*
	* This action is enabled only for admin access and requires developer credentials.
	* The ProviderName must match the value specified when creating an IdP for the pool.
	* To disable a native username + password user, the ProviderName value must be Cognito and the ProviderAttributeName must be Cognito_Subject, with the ProviderAttributeValue being the name that is used in the user pool for the user.
	* The ProviderAttributeName must always be Cognito_Subject for social identity providers. The ProviderAttributeValue must always be the exact subject that was used when the user was originally linked as a source user.
	* For de-linking a SAML identity, there are two scenarios. If the linked identity has not yet been used to sign-in, the ProviderAttributeName and ProviderAttributeValue must be the same values that were used for the SourceUser when the identities were originally linked using AdminLinkProviderForUser call. (If the linking was done with ProviderAttributeName set to Cognito_Subject, the same applies here). However, if the user has already signed in, the ProviderAttributeName must be Cognito_Subject and ProviderAttributeValue must be the subject of the SAML assertion.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminDisableProviderForUser* AdminDisableProviderForUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminDisableProviderForUserRequest& Request);
protected:
	FAdminDisableProviderForUserRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminDisableUser
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminDisableUserCallback, bool, bSuccess, const FAdminDisableUserResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminDisableUser : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminDisableUserCallback Callback;
public:
	/**
	 * Disables the specified user.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminDisableUser* AdminDisableUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminDisableUserRequest& Request);
protected:
	FAdminDisableUserRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminEnableUser
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminEnableUserCallback, bool, bSuccess, const FAdminEnableUserResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminEnableUser : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminEnableUserCallback Callback;
public:
	/**
	 * Enables the specified user as an administrator. Works on any user.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminEnableUser* AdminEnableUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminEnableUserRequest& Request);
protected:
	FAdminEnableUserRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminForgetDevice
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAdminForgetDeviceCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminForgetDevice : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminForgetDeviceCallback Callback;
public:
	/**
	 * Forgets the device, as an administrator.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminForgetDevice* AdminForgetDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminForgetDeviceRequest& Request);
protected:
	FAdminForgetDeviceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminGetDevice
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminGetDeviceCallback, bool, bSuccess, const FAdminGetDeviceResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminGetDevice : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminGetDeviceCallback Callback;
public:
	/**
	 * Gets the device, as an administrator.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminGetDevice* AdminGetDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminGetDeviceRequest& Request);
protected:
	FAdminGetDeviceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminGetUser
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminGetUserCallback, bool, bSuccess, const FAdminGetUserResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminGetUser : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminGetUserCallback Callback;
public:
	/**
	 * Gets the specified user by user name in a user pool as an administrator. Works on any user.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminGetUser* AdminGetUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminGetUserRequest& Request);
protected:
	FAdminGetUserRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminInitiateAuth
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminInitiateAuthCallback, bool, bSuccess, const FAdminInitiateAuthResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminInitiateAuth : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminInitiateAuthCallback Callback;
public:
	/**
	 * Initiates the authentication flow, as an administrator.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminInitiateAuth* AdminInitiateAuth(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminInitiateAuthRequest& Request);
protected:
	FAdminInitiateAuthRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminLinkProviderForUser
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminLinkProviderForUserCallback, bool, bSuccess, const FAdminLinkProviderForUserResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminLinkProviderForUser : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminLinkProviderForUserCallback Callback;
public:
	/**
	 * Links an existing user account in a user pool (DestinationUser) to an identity from an external identity provider (SourceUser) based on a specified attribute name and value from the external identity provider. This allows you to create a link from the existing user account to an external federated user identity that has not yet been used to sign in, so that the federated user identity can be used to sign in as the existing user account.
	 * For example, if there is an existing user with a username and password, this API links that user to a federated user identity, so that when the federated user identity is used, the user signs in as the existing user account.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminLinkProviderForUser* AdminLinkProviderForUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminLinkProviderForUserRequest& Request);
protected:
	FAdminLinkProviderForUserRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminListDevices
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminListDevicesCallback, bool, bSuccess, const FAdminListDevicesResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminListDevices : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminListDevicesCallback Callback;
public:
	/**
	 * Lists devices, as an administrator.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminListDevices* AdminListDevices(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminListDevicesRequest& Request);
protected:
	FAdminListDevicesRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminListGroupsForUser
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminListGroupsForUserCallback, bool, bSuccess, const FAdminListGroupsForUserResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminListGroupsForUser : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminListGroupsForUserCallback Callback;
public:
	/**
	 * Lists the groups that the user belongs to.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminListGroupsForUser* AdminListGroupsForUser(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminListGroupsForUserRequest& Request);
protected:
	FAdminListGroupsForUserRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminListUserAuthEvents
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminListUserAuthEventsCallback, bool, bSuccess, const FAdminListUserAuthEventsResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminListUserAuthEvents : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminListUserAuthEventsCallback Callback;
public:
	/**
	 * Lists a history of user activity and any risks detected as part of Amazon Cognito advanced security.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminListUserAuthEvents* AdminListUserAuthEvents(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminListUserAuthEventsRequest& Request);
protected:
	FAdminListUserAuthEventsRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognito
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAdminRemoveUserFromGroupCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminRemoveUserFromGroup : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminRemoveUserFromGroupCallback Callback;
public:
	/**
	 * Removes the specified user from the specified group.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminRemoveUserFromGroup* AdminRemoveUserFromGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminRemoveUserFromGroupRequest& Request);
protected:
	FAdminRemoveUserFromGroupRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminResetUserPassword
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminResetUserPasswordCallback, bool, bSuccess, const FAdminResetUserPasswordResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminResetUserPassword : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminResetUserPasswordCallback Callback;
public:
	/**
	 * Resets the specified user's password in a user pool as an administrator. Works on any user.
	 *
	 * When a developer calls this API, the current password is invalidated, so it must be changed. If a user tries to sign in after the API is called, the app will get a PasswordResetRequiredException exception back and should direct the user down the flow to reset the password, which is the same as the forgot password flow. In addition, if the user pool has phone verification selected and a verified phone number exists for the user, or if email verification is selected and a verified email exists for the user, calling this API will also result in sending a message to the end user with the code to change their password.
	 * Calling this action requires developer credentials.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminResetUserPassword* AdminResetUserPassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminResetUserPasswordRequest& Request);
protected:
	FAdminResetUserPasswordRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminRespondToAuthChallenge
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminRespondToAuthChallengeCallback, bool, bSuccess, const FAdminRespondToAuthChallengeResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminRespondToAuthChallenge : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminRespondToAuthChallengeCallback Callback;
public:
	/**
	 * Responds to an authentication challenge, as an administrator.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminRespondToAuthChallenge* AdminRespondToAuthChallenge(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminRespondToAuthChallengeRequest& Request);
protected:
	FAdminRespondToAuthChallengeRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminSetUserMFAPreference
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminSetUserMFAPreferenceCallback, bool, bSuccess, const FAdminSetUserMFAPreferenceResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminSetUserMFAPreference : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminSetUserMFAPreferenceCallback Callback;
public:
	/**
	 * Sets the user's multi-factor authentication (MFA) preference, including which MFA options are enabled and if any are preferred.
	 * Only one factor can be set as preferred. The preferred MFA factor will be used to authenticate a user if multiple factors are enabled. If multiple options are enabled and no preference is set, a challenge to choose an MFA option will be returned during sign in.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminSetUserMFAPreference* AdminSetUserMFAPreference(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminSetUserMFAPreferenceRequest& Request);
protected:
	FAdminSetUserMFAPreferenceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminSetUserPassword
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminSetUserPasswordCallback, bool, bSuccess, const FAdminSetUserPasswordResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminSetUserPassword : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminSetUserPasswordCallback Callback;
public:
	/**
	* Sets the specified user's password in a user pool as an administrator. Works on any user.
	*
	* The password can be temporary or permanent. If it is temporary, the user status will be placed into the FORCE_CHANGE_PASSWORD state. When the user next tries to sign in, the InitiateAuth/AdminInitiateAuth response will contain the NEW_PASSWORD_REQUIRED challenge. If the user does not sign in before it expires, the user will not be able to sign in and their password will need to be reset by an administrator.
	* Once the user has set a new password, or the password is permanent, the user status will be set to Confirmed.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminSetUserPassword* AdminSetUserPassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminSetUserPasswordRequest& Request);
protected:
	FAdminSetUserPasswordRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminSetUserSettings
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminSetUserSettingsCallback, bool, bSuccess, const FAdminSetUserSettingsResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminSetUserSettings : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminSetUserSettingsCallback Callback;
public:
	/**
	 * This action is no longer supported. You can use it to configure only SMS MFA. You can't use it to configure TOTP software token MFA. To configure either type of MFA, use AdminSetUserMFAPreference instead.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminSetUserSettings* AdminSetUserSettings(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminSetUserSettingsRequest& Request);
protected:
	FAdminSetUserSettingsRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminUpdateDeviceStatus
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminUpdateDeviceStatusCallback, bool, bSuccess, const FAdminUpdateDeviceStatusResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminUpdateDeviceStatus : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminUpdateDeviceStatusCallback Callback;
public:
	/**
	 * Updates the device status as an administrator.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminUpdateDeviceStatus* AdminUpdateDeviceStatus(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminUpdateDeviceStatusRequest& Request);
protected:
	FAdminUpdateDeviceStatusRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminUpdateUserAttributes
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminUpdateUserAttributesCallback, bool, bSuccess, const FAdminUpdateUserAttributesResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminUpdateUserAttributes : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminUpdateUserAttributesCallback Callback;
public:
	/**
	 * Updates the specified user's attributes, including developer attributes, as an administrator. Works on any user.
	 * For custom attributes, you must prepend the custom: prefix to the attribute name.
	 * In addition to updating user attributes, this API can also be used to mark phone and email as verified.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminUpdateUserAttributes* AdminUpdateUserAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminUpdateUserAttributesRequest& Request);
protected:
	FAdminUpdateUserAttributesRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAdminUserGlobalSignOut
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAdminUserGlobalSignOutCallback, bool, bSuccess, const FAdminUserGlobalSignOutResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAdminUserGlobalSignOut : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAdminUserGlobalSignOutCallback Callback;
public:
	/**
	 * Signs out users from all devices, as an administrator.
	 * It also invalidates all refresh tokens issued to a user. The user's current access and Id tokens remain valid until their expiry. Access and Id tokens expire one hour after they are issued.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAdminUserGlobalSignOut* AdminUserGlobalSignOut(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAdminUserGlobalSignOutRequest& Request);
protected:
	FAdminUserGlobalSignOutRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoAssociateSoftwareToken
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAssociateSoftwareTokenCallback, bool, bSuccess, const FAssociateSoftwareTokenResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoAssociateSoftwareToken : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAssociateSoftwareTokenCallback Callback;
public:
	/**
	 * Returns a unique generated shared secret key code for the user account. The Request takes an access token or a session string, but not both.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoAssociateSoftwareToken* AssociateSoftwareToken(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FAssociateSoftwareTokenRequest& Request);
protected:
	FAssociateSoftwareTokenRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoChangePassword
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnChangePasswordCallback, bool, bSuccess, const FChangePasswordResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoChangePassword : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnChangePasswordCallback Callback;
public:
	/**
	 * Changes the password for a specified user in a user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoChangePassword* ChangePassword(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FChangePasswordRequest& Request);
protected:
	FChangePasswordRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoConfirmDevice
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnConfirmDeviceCallback, bool, bSuccess, const FConfirmDeviceResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoConfirmDevice : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnConfirmDeviceCallback Callback;
public:
	/**
	 * Confirms tracking of the device. This API call is the call that begins device tracking.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoConfirmDevice* ConfirmDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FConfirmDeviceRequest& Request);
protected:
	FConfirmDeviceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoCreateGroup
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreateGroupCallback, bool, bSuccess, const FCreateGroupResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoCreateGroup : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCreateGroupCallback Callback;
public:
	/**
	 * Creates a new group in the specified user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoCreateGroup* CreateGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateGroupRequest& Request);
protected:
	FCreateGroupRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoCreateIdentityProvider
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreateIdentityProviderCallback, bool, bSuccess, const FCreateIdentityProviderResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoCreateIdentityProvider : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCreateIdentityProviderCallback Callback;
public:
	/**
	 * Creates an identity provider for a user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoCreateIdentityProvider* CreateIdentityProvider(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateIdentityProviderRequest& Request);
protected:
	FCreateIdentityProviderRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoCreateResourceServer
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreateResourceServerCallback, bool, bSuccess, const FCreateResourceServerResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoCreateResourceServer : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCreateResourceServerCallback Callback;
public:
	/**
	 * Creates a new OAuth2.0 resource server and defines custom scopes in it.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoCreateResourceServer* CreateResourceServer(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateResourceServerRequest& Request);
protected:
	FCreateResourceServerRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoCreateUserImportJob
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreateUserImportJobCallback, bool, bSuccess, const FCreateUserImportJobResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoCreateUserImportJob : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCreateUserImportJobCallback Callback;
public:
	/**
	 * Creates the user import job.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoCreateUserImportJob* CreateUserImportJob(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateUserImportJobRequest& Request);
protected:
	FCreateUserImportJobRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoCreateUserPool
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreateUserPoolCallback, bool, bSuccess, const FCreateUserPoolResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoCreateUserPool : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCreateUserPoolCallback Callback;
public:
	/**
	 * Creates a new Amazon Cognito user pool and sets the password policy for the pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoCreateUserPool* CreateUserPool(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateUserPoolRequest& Request);
protected:
	FCreateUserPoolRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoCreateUserPoolClient
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreateUserPoolClientCallback, bool, bSuccess, const FCreateUserPoolClientResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoCreateUserPoolClient : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCreateUserPoolClientCallback Callback;
public:
	/**
	 * Creates the user pool client.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoCreateUserPoolClient* CreateUserPoolClient(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateUserPoolClientRequest& Request);
protected:
	FCreateUserPoolClientRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoCreateUserPoolDomain
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCreateUserPoolDomainCallback, bool, bSuccess, const FCreateUserPoolDomainResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoCreateUserPoolDomain : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCreateUserPoolDomainCallback Callback;
public:
	/**
	 * Creates a new domain for a user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoCreateUserPoolDomain* CreateUserPoolDomain(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FCreateUserPoolDomainRequest& Request);
protected:
	FCreateUserPoolDomainRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDeleteGroup
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeleteGroupCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDeleteGroup : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeleteGroupCallback Callback;
public:
	/**
	 * Deletes a group. Currently only groups with no members can be deleted.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDeleteGroup* DeleteGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteGroupRequest& Request);
protected:
	FDeleteGroupRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDeleteIdentityProvider
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeleteIdentityProviderCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDeleteIdentityProvider : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeleteIdentityProviderCallback Callback;
public:
	/**
	 * Deletes an identity provider for a user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDeleteIdentityProvider* DeleteIdentityProvider(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteIdentityProviderRequest& Request);
protected:
	FDeleteIdentityProviderRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDeleteResourceServer
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeleteResourceServerCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDeleteResourceServer : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeleteResourceServerCallback Callback;
public:
	/**
	 * Deletes a resource server.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDeleteResourceServer* DeleteResourceServer(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteResourceServerRequest& Request);
protected:
	FDeleteResourceServerRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDeleteUserAttributes
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDeleteUserAttributesCallback, bool, bSuccess, const FDeleteUserAttributesResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDeleteUserAttributes : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeleteUserAttributesCallback Callback;
public:
	/**
	 * Deletes the attributes for a user.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDeleteUserAttributes* DeleteUserAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteUserAttributesRequest& Request);
protected:
	FDeleteUserAttributesRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDeleteUserPool
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeleteUserPoolCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDeleteUserPool : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeleteUserPoolCallback Callback;
public:
	/**
	 * Deletes the specified Amazon Cognito user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDeleteUserPool* DeleteUserPool(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteUserPoolRequest& Request);
protected:
	FDeleteUserPoolRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDeleteUserPoolClient
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDeleteUserPoolClientCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDeleteUserPoolClient : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeleteUserPoolClientCallback Callback;
public:
	/**
	 * Allows the developer to delete the user pool client.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDeleteUserPoolClient* DeleteUserPoolClient(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteUserPoolClientRequest& Request);
protected:
	FDeleteUserPoolClientRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDeleteUserPoolDomain
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDeleteUserPoolDomainCallback, bool, bSuccess, const FDeleteUserPoolDomainResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDeleteUserPoolDomain : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDeleteUserPoolDomainCallback Callback;
public:
	/**
	 * Deletes a domain for a user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDeleteUserPoolDomain* DeleteUserPoolDomain(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDeleteUserPoolDomainRequest& Request);
protected:
	FDeleteUserPoolDomainRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDescribeIdentityProvider
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDescribeIdentityProviderCallback, bool, bSuccess, const FDescribeIdentityProviderResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDescribeIdentityProvider : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDescribeIdentityProviderCallback Callback;
public:
	/**
	 * Gets information about a specific identity provider.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDescribeIdentityProvider* DescribeIdentityProvider(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeIdentityProviderRequest& Request);
protected:
	FDescribeIdentityProviderRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDescribeResourceServer
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDescribeResourceServerCallback, bool, bSuccess, const FDescribeResourceServerResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDescribeResourceServer : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDescribeResourceServerCallback Callback;
public:
	/**
	 * Describes a resource server.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDescribeResourceServer* DescribeResourceServer(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeResourceServerRequest& Request);
protected:
	FDescribeResourceServerRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDescribeRiskConfiguration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDescribeRiskConfigurationCallback, bool, bSuccess, const FDescribeRiskConfigurationResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDescribeRiskConfiguration : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDescribeRiskConfigurationCallback Callback;
public:
	/**
	 * Describes the risk configuration.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDescribeRiskConfiguration* DescribeRiskConfiguration(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeRiskConfigurationRequest& Request);
protected:
	FDescribeRiskConfigurationRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDescribeUserImportJob
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDescribeUserImportJobCallback, bool, bSuccess, const FDescribeUserImportJobResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDescribeUserImportJob : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDescribeUserImportJobCallback Callback;
public:
	/**
	 * Describes the user import job.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDescribeUserImportJob* DescribeUserImportJob(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeUserImportJobRequest& Request);
protected:
	FDescribeUserImportJobRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDescribeUserPool
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDescribeUserPoolCallback, bool, bSuccess, const FDescribeUserPoolResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDescribeUserPool : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDescribeUserPoolCallback Callback;
public:
	/**
	 * Returns the configuration information and metadata of the specified user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDescribeUserPool* DescribeUserPool(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeUserPoolRequest& Request);
protected:
	FDescribeUserPoolRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDescribeUserPoolClient
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDescribeUserPoolClientCallback, bool, bSuccess, const FDescribeUserPoolClientResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDescribeUserPoolClient : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDescribeUserPoolClientCallback Callback;
public:
	/**
	 * Client method for returning the configuration information and metadata of the specified user pool app client.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDescribeUserPoolClient* DescribeUserPoolClient(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeUserPoolClientRequest& Request);
protected:
	FDescribeUserPoolClientRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoDescribeUserPoolDomain
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDescribeUserPoolDomainCallback, bool, bSuccess, const FDescribeUserPoolDomainResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoDescribeUserPoolDomain : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnDescribeUserPoolDomainCallback Callback;
public:
	/**
	 * Gets information about a domain.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoDescribeUserPoolDomain* DescribeUserPoolDomain(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FDescribeUserPoolDomainRequest& Request);
protected:
	FDescribeUserPoolDomainRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoForgetDevice
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnForgetDeviceCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoForgetDevice : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnForgetDeviceCallback Callback;
public:
	/**
	 * Forgets the specified device.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoForgetDevice* ForgetDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FForgetDeviceRequest& Request);
protected:
	FForgetDeviceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGetCSVHeader
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetCSVHeaderCallback, bool, bSuccess, const FGetCSVHeaderResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGetCSVHeader : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetCSVHeaderCallback Callback;
public:
	/**
	 * Gets the header information for the .csv file to be used as input for the user import job.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGetCSVHeader* GetCSVHeader(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetCSVHeaderRequest& Request);
protected:
	FGetCSVHeaderRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGetDevice
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetDeviceCallback, bool, bSuccess, const FGetDeviceResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGetDevice : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetDeviceCallback Callback;
public:
	/**
	 * Gets the device.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGetDevice* GetDevice(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetDeviceRequest& Request);
protected:
	FGetDeviceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGetGroup
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetGroupCallback, bool, bSuccess, const FGetGroupResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGetGroup : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetGroupCallback Callback;
public:
	/**
	 * Gets a group.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGetGroup* GetGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetGroupRequest& Request);
protected:
	FGetGroupRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGetIdentityProviderByIdentifier
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetIdentityProviderByIdentifierCallback, bool, bSuccess, const FGetIdentityProviderByIdentifierResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGetIdentityProviderByIdentifier : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetIdentityProviderByIdentifierCallback Callback;
public:
	/**
	 * Gets the specified identity provider.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGetIdentityProviderByIdentifier* GetIdentityProviderByIdentifier(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetIdentityProviderByIdentifierRequest& Request);
protected:
	FGetIdentityProviderByIdentifierRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGetSigningCertificate
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetSigningCertificateCallback, bool, bSuccess, const FGetSigningCertificateResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGetSigningCertificate : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetSigningCertificateCallback Callback;
public:
	/**
	 * This method takes a user pool ID, and returns the signing certificate.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGetSigningCertificate* GetSigningCertificate(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetSigningCertificateRequest& Request);
protected:
	FGetSigningCertificateRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGetUICustomization
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetUICustomizationCallback, bool, bSuccess, const FGetUICustomizationResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGetUICustomization : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetUICustomizationCallback Callback;
public:
	/**
	 * Gets the UI Customization information for a particular app client's app UI, if there is something set.
	 * If nothing is set for the particular client, but there is an existing pool level customization (app clientId will be ALL), then that is returned. If nothing is present, then an empty shape is returned.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGetUICustomization* GetUICustomization(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetUICustomizationRequest& Request);
protected:
	FGetUICustomizationRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGetUserAttributeVerificationCode
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetUserAttributeVerificationCodeCallback, bool, bSuccess, const FGetUserAttributeVerificationCodeResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGetUserAttributeVerificationCode : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetUserAttributeVerificationCodeCallback Callback;
public:
	/**
	 * Gets the user attribute verification code for the specified attribute name.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGetUserAttributeVerificationCode* GetUserAttributeVerificationCode(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetUserAttributeVerificationCodeRequest& Request);
protected:
	FGetUserAttributeVerificationCodeRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGetUserPoolMfaConfig
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGetUserPoolMfaConfigCallback, bool, bSuccess, const FGetUserPoolMfaConfigResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGetUserPoolMfaConfig : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGetUserPoolMfaConfigCallback Callback;
public:
	/**
	 * Gets the user pool multi-factor authentication (MFA) configuration.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGetUserPoolMfaConfig* GetUserPoolMfaConfig(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGetUserPoolMfaConfigRequest& Request);
protected:
	FGetUserPoolMfaConfigRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoGlobalSignOut
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnGlobalSignOutCallback, bool, bSuccess, const FGlobalSignOutResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoGlobalSignOut : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGlobalSignOutCallback Callback;
public:
	/**
	 * Signs out users from all devices. It also invalidates all refresh tokens issued to a user.
	 * The user's current access and Id tokens remain valid until their expiry. Access and Id tokens expire one hour after they are issued.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoGlobalSignOut* GlobalSignOut(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FGlobalSignOutRequest& Request);
protected:
	FGlobalSignOutRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListDevices
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListDevicesCallback, bool, bSuccess, const FListDevicesResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListDevices : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListDevicesCallback Callback;
public:
	/**
	 * Lists the devices.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListDevices* ListDevices(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListDevicesRequest& Request);
protected:
	FListDevicesRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListGroups
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListGroupsCallback, bool, bSuccess, const FListGroupsResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListGroups : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListGroupsCallback Callback;
public:
	/**
	 * Lists the groups associated with a user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListGroups* ListGroups(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListGroupsRequest& Request);
protected:
	FListGroupsRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListIdentityProviders
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListIdentityProvidersCallback, bool, bSuccess, const FListIdentityProvidersResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListIdentityProviders : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListIdentityProvidersCallback Callback;
public:
	/**
	 * Lists information about all identity providers for a user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListIdentityProviders* ListIdentityProviders(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListIdentityProvidersRequest& Request);
protected:
	FListIdentityProvidersRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListResourceServers
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListResourceServersCallback, bool, bSuccess, const FListResourceServersResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListResourceServers : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListResourceServersCallback Callback;
public:
	/**
	 * Lists the resource servers for a user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListResourceServers* ListResourceServers(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListResourceServersRequest& Request);
protected:
	FListResourceServersRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListTagsForResource
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListTagsForResourceCallback, bool, bSuccess, const FListTagsForResourceResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListTagsForResource : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListTagsForResourceCallback Callback;
public:
	/**
	 * Lists the tags that are assigned to an Amazon Cognito user pool.
	 *
	 * A tag is a label that you can apply to user pools to categorize and manage them in different ways, such as by purpose, owner, environment, or other criteria.
	 * You can use this action up to 10 times per second, per account.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListTagsForResource* ListTagsForResource(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListTagsForResourceRequest& Request);
protected:
	FListTagsForResourceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListUserImportJobs
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListUserImportJobsCallback, bool, bSuccess, const FListUserImportJobsResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListUserImportJobs : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListUserImportJobsCallback Callback;
public:
	/**
	 * Lists the user import jobs.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListUserImportJobs* ListUserImportJobs(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUserImportJobsRequest& Request);
protected:
	FListUserImportJobsRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListUserPoolClients
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListUserPoolClientsCallback, bool, bSuccess, const FListUserPoolClientsResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListUserPoolClients : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListUserPoolClientsCallback Callback;
public:
	/**
	 * Lists the clients that have been created for the specified user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListUserPoolClients* ListUserPoolClients(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUserPoolClientsRequest& Request);
protected:
	FListUserPoolClientsRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListUserPools
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListUserPoolsCallback, bool, bSuccess, const FListUserPoolsResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListUserPools : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListUserPoolsCallback Callback;
public:
	/**
	 * Lists the user pools associated with an AWS account.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListUserPools* ListUserPools(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUserPoolsRequest& Request);
protected:
	FListUserPoolsRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListUsers
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListUsersCallback, bool, bSuccess, const FListUsersResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListUsers : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListUsersCallback Callback;
public:
	/**
	 * Lists the users in the Amazon Cognito user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListUsers* ListUsers(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUsersRequest& Request);
protected:
	FListUsersRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoListUsersInGroup
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnListUsersInGroupCallback, bool, bSuccess, const FListUsersInGroupResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoListUsersInGroup : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnListUsersInGroupCallback Callback;
public:
	/**
	 * Lists the users in the specified group.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoListUsersInGroup* ListUsersInGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FListUsersInGroupRequest& Request);
protected:
	FListUsersInGroupRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoSetRiskConfiguration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSetRiskConfigurationCallback, bool, bSuccess, const FSetRiskConfigurationResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoSetRiskConfiguration : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnSetRiskConfigurationCallback Callback;
public:
	/**
	 * Configures actions on detected risks. To delete the risk configuration for UserPoolId or ClientId, pass null values for all four configuration types.
	 *
	 * To enable Amazon Cognito advanced security features, update the user pool to include the UserPoolAddOns keyAdvancedSecurityMode.
	 * See UpdateUserPool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoSetRiskConfiguration* SetRiskConfiguration(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetRiskConfigurationRequest& Request);
protected:
	FSetRiskConfigurationRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoSetUICustomization
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSetUICustomizationCallback, bool, bSuccess, const FSetUICustomizationResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoSetUICustomization : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnSetUICustomizationCallback Callback;
public:
	/**
	 * Sets the UI customization information for a user pool's built-in app UI.

	 * You can specify app UI customization settings for a single client (with a specific clientId) or for all clients (by setting the clientId to ALL). 
	 * If you specify ALL, the default configuration will be used for every client that has no UI customization set previously.
	 * If you specify UI customization settings for a particular client, it will no longer fall back to the ALL configuration.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoSetUICustomization* SetUICustomization(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetUICustomizationRequest& Request);
protected:
	FSetUICustomizationRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoSetUserMFAPreference
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSetUserMFAPreferenceCallback, bool, bSuccess, const FSetUserMFAPreferenceResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoSetUserMFAPreference : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnSetUserMFAPreferenceCallback Callback;
public:
	/**
	 * Set the user's multi-factor authentication (MFA) method preference, including which MFA factors are enabled and if any are preferred.
	 * Only one factor can be set as preferred. The preferred MFA factor will be used to authenticate a user if multiple factors are enabled. If multiple options are enabled and no preference is set, a challenge to choose an MFA option will be returned during sign in.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoSetUserMFAPreference* SetUserMFAPreference(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetUserMFAPreferenceRequest& Request);
protected:
	FSetUserMFAPreferenceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoSetUserPoolMfaConfig
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSetUserPoolMfaConfigCallback, bool, bSuccess, const FSetUserPoolMfaConfigResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoSetUserPoolMfaConfig : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnSetUserPoolMfaConfigCallback Callback;
public:
	/**
	 * Set the user pool multi-factor authentication (MFA) configuration.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoSetUserPoolMfaConfig* SetUserPoolMfaConfig(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetUserPoolMfaConfigRequest& Request);
protected:
	FSetUserPoolMfaConfigRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoSetUserSettings
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSetUserSettingsCallback, bool, bSuccess, const FSetUserSettingsResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoSetUserSettings : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnSetUserSettingsCallback Callback;
public:
	/**
	 * This action is no longer supported. 
	 * You can use it to configure only SMS MFA. You can't use it to configure TOTP software token MFA. To configure either type of MFA, use SetUserMFAPreference instead.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoSetUserSettings* SetUserSettings(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FSetUserSettingsRequest& Request);
protected:
	FSetUserSettingsRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoStartUserImportJob
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStartUserImportJobCallback, bool, bSuccess, const FStartUserImportJobResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoStartUserImportJob : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnStartUserImportJobCallback Callback;
public:
	/**
	 * Starts the user import.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoStartUserImportJob* StartUserImportJob(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FStartUserImportJobRequest& Request);
protected:
	FStartUserImportJobRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoStopUserImportJob
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStopUserImportJobCallback, bool, bSuccess, const FStopUserImportJobResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoStopUserImportJob : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnStopUserImportJobCallback Callback;
public:
	/**
	 * Stops the user import job.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoStopUserImportJob* StopUserImportJob(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FStopUserImportJobRequest& Request);
protected:
	FStopUserImportJobRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoTagResource
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCognitoTagResourceCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoTagResource : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCognitoTagResourceCallback Callback;
public:
	/**
	 * Assigns a set of tags to an Amazon Cognito user pool. A tag is a label that you can use to categorize and manage user pools in different ways, such as by purpose, owner, environment, or other criteria.
	 *
	 * Each tag consists of a key and value, both of which you define. A key is a general category for more specific values. For example, if you have two versions of a user pool, one for testing and another for production, you might assign an Environment tag key to both user pools. The value of this key might be Test for one user pool and Production for the other.
	 * Tags are useful for cost tracking and access control. You can activate your tags so that they appear on the Billing and Cost Management console, where you can track the costs associated with your user pools. In an IAM policy, you can constrain permissions for user pools based on specific tags or tag values.
	 * You can use this action up to 5 times per second, per account. A user pool can have as many as 50 tags.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoTagResource* TagResource(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FTagResourceRequest& Request);
protected:
	FTagResourceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUntagResource
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCognitoUntagResourceCallback, bool, bSuccess, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUntagResource : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCognitoUntagResourceCallback Callback;
public:
	/**
	 * Removes the specified tags from an Amazon Cognito user pool. You can use this action up to 5 times per second, per account
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUntagResource* UntagResource(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUntagResourceRequest& Request);
protected:
	FUntagResourceRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUpdateAuthEventFeedback
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateAuthEventFeedbackCallback, bool, bSuccess, const FUpdateAuthEventFeedbackResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUpdateAuthEventFeedback : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateAuthEventFeedbackCallback Callback;
public:
	/**
	 * Provides the feedback for an authentication event whether it was from a valid user or not.
	 * This feedback is used for improving the risk evaluation decision for the user pool as part of Amazon Cognito advanced security.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUpdateAuthEventFeedback* UpdateAuthEventFeedback(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateAuthEventFeedbackRequest& Request);
protected:
	FUpdateAuthEventFeedbackRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUpdateDeviceStatus
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateDeviceStatusCallback, bool, bSuccess, const FUpdateDeviceStatusResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUpdateDeviceStatus : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateDeviceStatusCallback Callback;
public:
	/**
	 * Updates the device status.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUpdateDeviceStatus* UpdateDeviceStatus(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateDeviceStatusRequest& Request);
protected:
	FUpdateDeviceStatusRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUpdateGroup
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateGroupCallback, bool, bSuccess, const FUpdateGroupResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUpdateGroup : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateGroupCallback Callback;
public:
	/**
	 * Updates the specified group with the specified attributes.
	 *
	 * Calling this action requires developer credentials.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUpdateGroup* UpdateGroup(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateGroupRequest& Request);
protected:
	FUpdateGroupRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUpdateIdentityProvider
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateIdentityProviderCallback, bool, bSuccess, const FUpdateIdentityProviderResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUpdateIdentityProvider : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateIdentityProviderCallback Callback;
public:
	/**
	 * Updates identity provider information for a user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUpdateIdentityProvider* UpdateIdentityProvider(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateIdentityProviderRequest& Request);
protected:
	FUpdateIdentityProviderRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUpdateResourceServer
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateResourceServerCallback, bool, bSuccess, const FUpdateResourceServerResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUpdateResourceServer : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateResourceServerCallback Callback;
public:
	/**
	 * Updates the name and scopes of resource server. All other fields are read-only.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUpdateResourceServer* UpdateResourceServer(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateResourceServerRequest& Request);
protected:
	FUpdateResourceServerRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUpdateUserAttributes
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateUserAttributesCallback, bool, bSuccess, const FUpdateUserAttributesResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUpdateUserAttributes : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateUserAttributesCallback Callback;
public:
	/**
	 * Allows a user to update a specific attribute (one at a time).
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUpdateUserAttributes* UpdateUserAttributes(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateUserAttributesRequest& Request);
protected:
	FUpdateUserAttributesRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUpdateUserPool
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateUserPoolCallback, bool, bSuccess, const FUpdateUserPoolResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUpdateUserPool : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateUserPoolCallback Callback;
public:
	/**
	 * Updates the specified user pool with the specified attributes. You can get a list of the current user pool settings using DescribeUserPool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUpdateUserPool* UpdateUserPool(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateUserPoolRequest& Request);
protected:
	FUpdateUserPoolRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUpdateUserPoolClient
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateUserPoolClientCallback, bool, bSuccess, const FUpdateUserPoolClientResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUpdateUserPoolClient : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateUserPoolClientCallback Callback;
public:
	/**
	 * Updates the specified user pool app client with the specified attributes. You can get a list of the current user pool app client settings using DescribeUserPoolClient.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUpdateUserPoolClient* UpdateUserPoolClient(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateUserPoolClientRequest& Request);
protected:
	FUpdateUserPoolClientRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoUpdateUserPoolDomain
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnUpdateUserPoolDomainCallback, bool, bSuccess, const FUpdateUserPoolDomainResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoUpdateUserPoolDomain : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnUpdateUserPoolDomainCallback Callback;
public:
	/**
	 * Updates the Secure Sockets Layer (SSL) certificate for the custom domain for your user pool.
	 *
	 * You can use this operation to provide the Amazon Resource Name (ARN) of a new certificate to Amazon Cognito. You cannot use it to change the domain for a user pool.
	 * A custom domain is used to host the Amazon Cognito hosted UI, which provides sign-up and sign-in pages for your application. When you set up a custom domain, you provide a certificate that you manage with AWS Certificate Manager (ACM). When necessary, you can use this operation to change the certificate that you applied to your custom domain.
	 * Usually, this is unnecessary following routine certificate renewal with ACM. When you renew your existing certificate in ACM, the ARN for your certificate remains the same, and your custom domain uses the new certificate automatically.
	 * However, if you replace your existing certificate with a new one, ACM gives the new certificate a new ARN. To apply the new certificate to your custom domain, you must provide this ARN to Amazon Cognito.
	 * When you add your new certificate in ACM, you must choose US East (N. Virginia) as the AWS Region.
	 * After you submit your Request, Amazon Cognito requires up to 1 hour to distribute your new certificate to your custom domain.
	 * For more information about adding a custom domain to your user pool, see Using Your Own Domain for the Hosted UI.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoUpdateUserPoolDomain* UpdateUserPoolDomain(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FUpdateUserPoolDomainRequest& Request);
protected:
	FUpdateUserPoolDomainRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoVerifySoftwareToken
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnVerifySoftwareTokenCallback, bool, bSuccess, const FVerifySoftwareTokenResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoVerifySoftwareToken : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnVerifySoftwareTokenCallback Callback;
public:
	/**
	 * Use this API to register a user's entered TOTP code and mark the user's software token MFA status as "verified" if successful. The Request takes an access token or a session string, but not both.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoVerifySoftwareToken* VerifySoftwareToken(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FVerifySoftwareTokenRequest& Request);
protected:
	FVerifySoftwareTokenRequest m_RequestData;
public:
	virtual void Activate() override;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
//		UCognitoVerifyUserAttribute
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnVerifyUserAttributeCallback, bool, bSuccess, const FVerifyUserAttributeResult&, Result, ECognitoIdentityProviderErrors, ErrorType, const FString&, ErrorMessage);

UCLASS()
class COGNITO_API UCognitoVerifyUserAttribute : public UCognitoAsync
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnVerifyUserAttributeCallback Callback;
public:
	/**
	 * Verifies the specified user attributes in the user pool.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", Category = "AWS|Cognito", BlueprintInternalUseOnly="true"))
	static UCognitoVerifyUserAttribute* VerifyUserAttribute(UObject* WorldContextObject, UCognitoIdpPlatform* CognitoPlatform, const FVerifyUserAttributeRequest& Request);
protected:
	FVerifyUserAttributeRequest m_RequestData;
public:
	virtual void Activate() override;
};
