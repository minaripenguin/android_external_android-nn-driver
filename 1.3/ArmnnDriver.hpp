//
// Copyright © 2020 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <HalInterfaces.h>

#include "../ArmnnDevice.hpp"
#include "ArmnnDriverImpl.hpp"
#include "HalPolicy.hpp"

#include "../ArmnnDriverImpl.hpp"
#include "../1.3/ArmnnDriverImpl.hpp"
#include "../1.3/HalPolicy.hpp"
#include "../1.2/ArmnnDriverImpl.hpp"
#include "../1.2/HalPolicy.hpp"
#include "../1.1/ArmnnDriverImpl.hpp"
#include "../1.1/HalPolicy.hpp"
#include "../1.0/ArmnnDriverImpl.hpp"
#include "../1.0/HalPolicy.hpp"

#include <log/log.h>

namespace armnn_driver
{
namespace hal_1_3
{

class ArmnnDriver : public ArmnnDevice, public V1_3::IDevice
{
public:

    ArmnnDriver(DriverOptions options)
        : ArmnnDevice(std::move(options))
    {
        ALOGV("hal_1_3::ArmnnDriver::ArmnnDriver()");
    }
    ~ArmnnDriver() {}

    using HidlToken = android::hardware::hidl_array<uint8_t, ANEURALNETWORKS_BYTE_SIZE_OF_CACHE_TOKEN>;

public:
    Return<void> getCapabilities(V1_0::IDevice::getCapabilities_cb cb) override
    {
        ALOGV("hal_1_3::ArmnnDriver::getCapabilities()");

        return hal_1_0::ArmnnDriverImpl::getCapabilities(m_Runtime, cb);
    }

    Return<void> getSupportedOperations(const V1_0::Model& model,
                                        V1_0::IDevice::getSupportedOperations_cb cb) override
    {
        ALOGV("hal_1_3::ArmnnDriver::getSupportedOperations()");

        return armnn_driver::ArmnnDriverImpl<hal_1_0::HalPolicy>::getSupportedOperations(m_Runtime,
                                                                                         m_Options,
                                                                                         model,
                                                                                         cb);
    }

    Return<V1_0::ErrorStatus> prepareModel(const V1_0::Model& model,
                                           const android::sp<V1_0::IPreparedModelCallback>& cb) override
    {
        ALOGV("hal_1_3::ArmnnDriver::prepareModel()");

        return armnn_driver::ArmnnDriverImpl<hal_1_0::HalPolicy>::prepareModel(m_Runtime,
                                                                               m_ClTunedParameters,
                                                                               m_Options,
                                                                               model,
                                                                               cb);
    }

    Return<void> getCapabilities_1_1(V1_1::IDevice::getCapabilities_1_1_cb cb) override
    {
        ALOGV("hal_1_3::ArmnnDriver::getCapabilities_1_1()");

        return hal_1_1::ArmnnDriverImpl::getCapabilities_1_1(m_Runtime, cb);
    }

    Return<void> getSupportedOperations_1_1(const V1_1::Model& model,
                                            V1_1::IDevice::getSupportedOperations_1_1_cb cb) override
    {
        ALOGV("hal_1_3::ArmnnDriver::getSupportedOperations_1_1()");
        return armnn_driver::ArmnnDriverImpl<hal_1_1::HalPolicy>::getSupportedOperations(m_Runtime,
                                                                                         m_Options,
                                                                                         model,
                                                                                         cb);
    }

    Return<V1_0::ErrorStatus> prepareModel_1_1(const V1_1::Model& model,
                                               V1_1::ExecutionPreference preference,
                                               const android::sp<V1_0::IPreparedModelCallback>& cb) override
    {
        ALOGV("hal_1_3::ArmnnDriver::prepareModel_1_1()");

        if (!(preference == ExecutionPreference::LOW_POWER ||
              preference == ExecutionPreference::FAST_SINGLE_ANSWER ||
              preference == ExecutionPreference::SUSTAINED_SPEED))
        {
            ALOGV("hal_1_3::ArmnnDriver::prepareModel_1_1: Invalid execution preference");
            cb->notify(V1_0::ErrorStatus::INVALID_ARGUMENT, nullptr);
            return V1_0::ErrorStatus::INVALID_ARGUMENT;
        }

        return armnn_driver::ArmnnDriverImpl<hal_1_1::HalPolicy>::prepareModel(m_Runtime,
                                                                               m_ClTunedParameters,
                                                                               m_Options,
                                                                               model,
                                                                               cb,
                                                                               model.relaxComputationFloat32toFloat16
                                                                               && m_Options.GetFp16Enabled());
    }

    Return<void> getCapabilities_1_2(getCapabilities_1_2_cb cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::getCapabilities()");

        return hal_1_2::ArmnnDriverImpl::getCapabilities_1_2(m_Runtime, cb);
    }

    Return<void> getSupportedOperations_1_2(const V1_2::Model& model,
                                            getSupportedOperations_1_2_cb cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::getSupportedOperations()");

        return armnn_driver::ArmnnDriverImpl<hal_1_2::HalPolicy>::getSupportedOperations(m_Runtime,
                                                                                         m_Options,
                                                                                         model,
                                                                                         cb);
    }

    Return<V1_0::ErrorStatus> prepareModel_1_2(const V1_2::Model& model, V1_1::ExecutionPreference preference,
            const android::hardware::hidl_vec<android::hardware::hidl_handle>&,
            const android::hardware::hidl_vec<android::hardware::hidl_handle>&, const HidlToken&,
            const android::sp<V1_2::IPreparedModelCallback>& cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::prepareModel_1_2()");

        if (!(preference == ExecutionPreference::LOW_POWER ||
              preference == ExecutionPreference::FAST_SINGLE_ANSWER ||
              preference == ExecutionPreference::SUSTAINED_SPEED))
        {
            ALOGV("hal_1_3::ArmnnDriver::prepareModel_1_2: Invalid execution preference");
            cb->notify(V1_0::ErrorStatus::INVALID_ARGUMENT, nullptr);
            return V1_0::ErrorStatus::INVALID_ARGUMENT;
        }

        return hal_1_2::ArmnnDriverImpl::prepareArmnnModel_1_2(m_Runtime,
                                                               m_ClTunedParameters,
                                                               m_Options,
                                                               model,
                                                               cb,
                                                               model.relaxComputationFloat32toFloat16
                                                               && m_Options.GetFp16Enabled());
    }

    Return<void> getCapabilities_1_3(getCapabilities_1_3_cb cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::getCapabilities()");

        return hal_1_3::ArmnnDriverImpl::getCapabilities_1_3(m_Runtime, cb);
    }

    Return<void> getSupportedOperations_1_3(const V1_3::Model& model,
                                            getSupportedOperations_1_3_cb cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::getSupportedOperations()");

        return armnn_driver::ArmnnDriverImpl<hal_1_3::HalPolicy>::getSupportedOperations(m_Runtime,
                                                                                         m_Options,
                                                                                         model,
                                                                                         cb);
    }

    Return<V1_3::ErrorStatus> prepareModel_1_3(const V1_3::Model& model,
                                               V1_1::ExecutionPreference preference,
                                               V1_3::Priority priority,
                                               const V1_3::OptionalTimePoint&,
                                               const android::hardware::hidl_vec<android::hardware::hidl_handle>&,
                                               const android::hardware::hidl_vec<android::hardware::hidl_handle>&,
                                               const HidlToken&,
                                               const android::sp<V1_3::IPreparedModelCallback>& cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::prepareModel_1_3()");

        if (!(preference == ExecutionPreference::LOW_POWER ||
              preference == ExecutionPreference::FAST_SINGLE_ANSWER ||
              preference == ExecutionPreference::SUSTAINED_SPEED))
        {
            ALOGV("hal_1_3::ArmnnDriver::prepareModel_1_3: Invalid execution preference");
            cb->notify_1_3(V1_3::ErrorStatus::INVALID_ARGUMENT, nullptr);
            return V1_3::ErrorStatus::INVALID_ARGUMENT;
        }

        if (!android::nn::validatePriority(priority)) {
            cb->notify_1_3(V1_3::ErrorStatus::INVALID_ARGUMENT, nullptr);
            return V1_3::ErrorStatus::INVALID_ARGUMENT;
        }


        return ArmnnDriverImpl::prepareArmnnModel_1_3(m_Runtime,
                                                      m_ClTunedParameters,
                                                      m_Options,
                                                      model,
                                                      cb,
                                                      model.relaxComputationFloat32toFloat16
                                                      && m_Options.GetFp16Enabled());
    }

    Return<void> getSupportedExtensions(getSupportedExtensions_cb cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::getSupportedExtensions()");
        cb(V1_0::ErrorStatus::NONE, {/* No extensions. */});
        return Void();
    }

    Return<void> getNumberOfCacheFilesNeeded(getNumberOfCacheFilesNeeded_cb cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::getSupportedExtensions()");

        // Set both numbers to be 0 for cache not supported.
        cb(V1_0::ErrorStatus::NONE, 0, 0);
        return Void();
    }

    Return<DeviceStatus> getStatus() override
    {
        ALOGV("hal_1_3::ArmnnDriver::getStatus()");

        return armnn_driver::ArmnnDriverImpl<hal_1_3::HalPolicy>::getStatus();
    }

    Return<void> getVersionString(getVersionString_cb cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::getVersionString()");

        cb(V1_0::ErrorStatus::NONE, "ArmNN");
        return Void();
    }

    Return<void> getType(getType_cb cb)
    {
        ALOGV("hal_1_3::ArmnnDriver::getType()");

        cb(V1_0::ErrorStatus::NONE, V1_2::DeviceType::CPU);
        return Void();
    }

    Return<V1_0::ErrorStatus> prepareModelFromCache(
        const android::hardware::hidl_vec<android::hardware::hidl_handle>&,
        const android::hardware::hidl_vec<android::hardware::hidl_handle>&,
        const HidlToken&,
        const sp<V1_2::IPreparedModelCallback>& callback)
    {
        ALOGV("hal_1_3::ArmnnDriver::prepareModelFromCache()");
        callback->notify_1_2(V1_0::ErrorStatus::GENERAL_FAILURE, nullptr);
        return V1_0::ErrorStatus::GENERAL_FAILURE;
    }

    Return<ErrorStatus> prepareModelFromCache_1_3(
        const V1_3::OptionalTimePoint&,
        const android::hardware::hidl_vec<android::hardware::hidl_handle>&,
        const android::hardware::hidl_vec<android::hardware::hidl_handle>&,
        const HidlToken&,
        const sp<V1_3::IPreparedModelCallback>& callback)
    {
        ALOGV("hal_1_3::ArmnnDriver::prepareModelFromCache()");
        callback->notify_1_3(ErrorStatus::GENERAL_FAILURE, nullptr);
        return ErrorStatus::GENERAL_FAILURE;
    }

    Return<void> allocate(const V1_3::BufferDesc& /*desc*/,
                          const hidl_vec<sp<V1_3::IPreparedModel>>& /*preparedModels*/,
                          const hidl_vec<V1_3::BufferRole>& /*inputRoles*/,
                          const hidl_vec<V1_3::BufferRole>& /*outputRoles*/,
                          allocate_cb cb) {
        ALOGV("hal_1_3::ArmnnDriver::allocate()");
        cb(ErrorStatus::GENERAL_FAILURE, nullptr, 0);
        return Void();
    }

};

} // namespace hal_1_3
} // namespace armnn_driver
