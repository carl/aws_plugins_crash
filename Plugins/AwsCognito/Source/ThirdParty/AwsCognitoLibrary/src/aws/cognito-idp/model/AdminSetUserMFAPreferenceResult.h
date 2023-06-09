﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/cognito-idp/CognitoIdentityProvider_EXPORTS.h>

namespace Aws
{
template<typename RESULT_TYPE>
class AmazonWebServiceResult;

namespace Utils
{
namespace Json
{
  class JsonValue;
} // namespace Json
} // namespace Utils
namespace CognitoIdentityProvider
{
namespace Model
{
  class AdminSetUserMFAPreferenceResult
  {
  public:
    AWS_COGNITOIDENTITYPROVIDER_API AdminSetUserMFAPreferenceResult();
    AWS_COGNITOIDENTITYPROVIDER_API AdminSetUserMFAPreferenceResult(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);
    AWS_COGNITOIDENTITYPROVIDER_API AdminSetUserMFAPreferenceResult& operator=(const Aws::AmazonWebServiceResult<Aws::Utils::Json::JsonValue>& result);

  };

} // namespace Model
} // namespace CognitoIdentityProvider
} // namespace Aws