#include "fmu_instance.hpp"

#include <cstdlib>
#include <jni.h>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_load(JNIEnv* env, jobject, jstring dir, jstring libName, jstring modelIdentifier)
{
    const char* _dir = env->GetStringUTFChars(dir, nullptr);
    const char* _libName = env->GetStringUTFChars(libName, nullptr);
    const char* _modelIdentifier = env->GetStringUTFChars(modelIdentifier, nullptr);
    auto* fmu = new FmuInstance(_dir, _libName, _modelIdentifier);
    env->ReleaseStringUTFChars(dir, _dir);
    env->ReleaseStringUTFChars(libName, _libName);
    env->ReleaseStringUTFChars(modelIdentifier, _modelIdentifier);
    return (jlong)fmu;
}

JNIEXPORT jstring JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getVersion(JNIEnv* env, jobject, jlong p)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiGetVersionTYPE* fmiGetVersion = fmu->fmiGetVersion_;
    const char* version = (*fmiGetVersion)();
    return env->NewStringUTF(version);
}

JNIEXPORT jstring JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getTypesPlatform(JNIEnv* env, jobject, jlong p)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiGetTypesPlatformTYPE* fmiGetTypesPlatform = fmu->fmiGetTypesPlatform_;
    const char* platform = (*fmiGetTypesPlatform)();
    return env->NewStringUTF(platform);
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setDebugLogging(JNIEnv* env, jobject, jlong p, jlong c, jboolean loggingOn)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiSetDebugLoggingTYPE* fmiSetDebugLogging = fmu->fmiSetDebugLogging_;
    fmiStatus status = (*fmiSetDebugLogging)((void*)c, (fmiBoolean)loggingOn);
    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getInteger(JNIEnv* env, jobject, jlong p, jlong c, jlongArray vr, jint nvr, jintArray ref)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    jlong* _vr = env->GetLongArrayElements(vr, nullptr);

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    fmiGetIntegerTYPE* fmiGetInteger = fmu->fmiGetInteger_;

    auto* _ref = (fmiInteger*)malloc(sizeof(fmiInteger) * nvr);
    fmiStatus status = (*fmiGetInteger)((void*)c, __vr, nvr, _ref);

    env->SetIntArrayRegion(ref, 0, nvr, (jint*)_ref);

    free(_ref);
    free(__vr);
    env->ReleaseLongArrayElements(vr, _vr, 0);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getReal(JNIEnv* env, jobject, jlong p, jlong c, jlongArray vr, jint nvr, jdoubleArray ref)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    jlong* _vr = env->GetLongArrayElements(vr, nullptr);

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    fmiGetRealTYPE* fmiGetReal = fmu->fmiGetReal_;

    auto _ref = (fmiReal*)malloc(sizeof(fmiReal) * nvr);
    fmiStatus status = (*fmiGetReal)((void*)c, __vr, nvr, _ref);

    env->SetDoubleArrayRegion(ref, 0, nvr, _ref);

    free(_ref);
    free(__vr);
    env->ReleaseLongArrayElements(vr, _vr, 0);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getRealDirect(JNIEnv* env, jobject obj, jlong p, jlong c, jobject vr, jint nvr, jdoubleArray ref)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    auto _vr = static_cast<jlong*>(env->GetDirectBufferAddress(vr));
    auto _ref = static_cast<fmiReal*>(env->GetDirectBufferAddress(ref));

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    fmiGetRealTYPE* fmiGetReal = fmu->fmiGetReal_;
    fmiStatus status = (*fmiGetReal)((void*)c, __vr, nvr, _ref);

    free(__vr);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getBoolean(JNIEnv* env, jobject, jlong p, jlong c, jlongArray vr, jint nvr, jbooleanArray ref)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    jlong* _vr = env->GetLongArrayElements(vr, nullptr);

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    auto _ref = (fmiBoolean*)malloc(sizeof(fmiBoolean*) * nvr);

    fmiGetBooleanTYPE* fmiGetBoolean = fmu->fmiGetBoolean_;
    fmiStatus status = (*fmiGetBoolean)((void*)c, __vr, nvr, _ref);

    for (auto i = 0; i < nvr; i++) {
        auto value = (jboolean)_ref[i];
        env->SetBooleanArrayRegion(ref, i, 1, &value);
    }

    free(_ref);
    free(__vr);
    env->ReleaseLongArrayElements(vr, _vr, 0);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getString(JNIEnv* env, jobject, jlong p, jlong c, jlongArray vr, jint nvr, jobjectArray ref)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    jlong* _vr = env->GetLongArrayElements(vr, nullptr);

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    fmiGetStringTYPE* fmiGetString = fmu->fmiGetString_;

    std::vector<const char*> _ref(nvr);
    for (auto i = 0; i < nvr; i++) {
        auto str = (jstring)env->GetObjectArrayElement(ref, i);
        _ref[i] = env->GetStringUTFChars(str, nullptr);
    }

    fmiStatus status = (*fmiGetString)((void*)c, __vr, nvr, _ref.data());

    for (auto i = 0; i < nvr; i++) {
        jstring value = env->NewStringUTF(_ref[i]);
        env->SetObjectArrayElement(ref, i, value);
    }

    env->ReleaseLongArrayElements(vr, _vr, 0);

    free(__vr);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getAll(
    JNIEnv* env, jobject obj, jlong p, jlong c,
    jlongArray intVr, jint nIntvr, jintArray intRef,
    jlongArray realVr, jint nRealvr, jdoubleArray realRef,
    jlongArray boolVr, jint nBoolvr, jbooleanArray boolRef,
    jlongArray strVr, jint nStrvr, jobjectArray strRef)
{
    jint intStatus = Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getInteger(env, obj, p, c, intVr, nIntvr, intRef);
    jint realStatus = Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getReal(
        env, obj, p, c, realVr, nRealvr, realRef);
    jint boolStatus = Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getBoolean(
        env, obj, p, c, boolVr, nBoolvr, boolRef);
    jint strStatus = Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_getString(
        env, obj, p, c, strVr, nStrvr, strRef);

    return (intStatus + realStatus + boolStatus + strStatus == 4) ? JNI_TRUE : JNI_FALSE;
}


JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setInteger(JNIEnv* env, jobject, jlong p, jlong c, jlongArray vr, jint nvr, jintArray values)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    jlong* _vr = env->GetLongArrayElements(vr, nullptr);
    jint* _values = env->GetIntArrayElements(values, nullptr);

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    fmiSetIntegerTYPE* fmiSetInteger = fmu->fmiSetInteger_;
    fmiStatus status = (*fmiSetInteger)((void*)c, __vr, nvr, (fmiInteger*)_values);

    env->ReleaseLongArrayElements(vr, _vr, 0);
    env->ReleaseIntArrayElements(values, _values, 0);

    free(__vr);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setReal(JNIEnv* env, jobject, jlong p, jlong c, jlongArray vr, jint nvr, jdoubleArray values)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    jlong* _vr = env->GetLongArrayElements(vr, nullptr);
    jdouble* _values = env->GetDoubleArrayElements(values, nullptr);

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    fmiSetRealTYPE* fmiSetReal = fmu->fmiSetReal_;
    fmiStatus status = (*fmiSetReal)((void*)c, __vr, nvr, _values);

    env->ReleaseLongArrayElements(vr, _vr, 0);
    env->ReleaseDoubleArrayElements(values, _values, 0);

    free(__vr);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setRealDirect(JNIEnv* env, jobject obj, jlong p, jlong c, jobject vr, jint nvr, jobject values)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    auto _vr = static_cast<jlong*>(env->GetDirectBufferAddress(vr));
    auto _values = static_cast<fmiReal*>(env->GetDirectBufferAddress(values));

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    fmiSetRealTYPE* fmiSetReal = fmu->fmiSetReal_;
    fmiStatus status = (*fmiSetReal)((void*)c, __vr, nvr, _values);

    free(__vr);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setBoolean(JNIEnv* env, jobject, jlong p, jlong c, jlongArray vr, jint nvr, jbooleanArray values)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    jlong* _vr = env->GetLongArrayElements(vr, nullptr);
    jboolean* _values = env->GetBooleanArrayElements(values, nullptr);

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    fmiSetBooleanTYPE* fmiSetBoolean = fmu->fmiSetBoolean_;
    fmiStatus status = (*fmiSetBoolean)((void*)c, __vr, nvr, (fmiBoolean*)_values);

    env->ReleaseLongArrayElements(vr, _vr, 0);
    env->ReleaseBooleanArrayElements(values, _values, 0);

    free(__vr);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setString(JNIEnv* env, jobject, jlong p, jlong c, jlongArray vr, jint nvr, jobjectArray values)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    jlong* _vr = env->GetLongArrayElements(vr, nullptr);

    auto __vr = (fmiValueReference*)malloc(sizeof(fmiValueReference) * nvr);
    for (auto i = 0; i < nvr; ++i) {
        __vr[i] = (fmiValueReference)_vr[i];
    }

    std::vector<const char*> _values(nvr);
    for (auto i = 0; i < nvr; i++) {
        auto str = (jstring)env->GetObjectArrayElement(values, i);
        _values[i] = env->GetStringUTFChars(str, nullptr);
    }

    fmiSetStringTYPE* fmiSetString = fmu->fmiSetString_;
    fmiStatus status = (*fmiSetString)((void*)c, __vr, nvr, _values.data());

    env->ReleaseLongArrayElements(vr, _vr, 0);

    free(__vr);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setAll(
    JNIEnv* env, jobject obj, jlong p, jlong c,
    jlongArray intVr, jint nIntvr, jintArray intValues,
    jlongArray realVr, jint nRealvr, jdoubleArray realValues,
    jlongArray boolVr, jint nBoolVr, jbooleanArray boolValues,
    jlongArray strVr, jint nStrvr, jobjectArray strValues)
{
    jint intStatus = Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setInteger(
        env, obj, p, c, intVr, nIntvr, intValues);
    jint realStatus = Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setReal(
        env, obj, p, c, realVr, nRealvr, realValues);
    jint boolStatus = Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setBoolean(
        env, obj, p, c, boolVr, nBoolVr, boolValues);
    jint strStatus = Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_setString(
        env, obj, p, c, strVr, nStrvr, strValues);

    return (intStatus + realStatus + boolStatus + strStatus == 4) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1Library_free(JNIEnv*, jobject, jlong p)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    jboolean status = 0;
    if (fmu->handle_) {
#ifdef WIN32
        status = FreeLibrary(fmu->handle_);
#else
        status = dlclose(fmu->handle_) == 0;
#endif
        fmu->handle_ = nullptr;
    }
    free(fmu);

    return status;
}


/***************************************************
Functions for FMI for Model Exchange
****************************************************/
JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1ModelExchangeLibrary_instantiateModel(JNIEnv* env, jobject, jlong p, jstring instanceName, jstring guid, jboolean loggingOn)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    const char* _instanceName = env->GetStringUTFChars(instanceName, nullptr);
    const char* _guid = env->GetStringUTFChars(guid, nullptr);

    fmiInstantiateModelTYPE* fmiInstantiate = fmu->fmiInstantiateModel_;
    fmiComponent c = (*fmiInstantiate)(_instanceName, _guid, fmu->meCallback_, (fmiBoolean)loggingOn);

    env->ReleaseStringUTFChars(instanceName, _instanceName);
    env->ReleaseStringUTFChars(guid, _guid);

    return (jlong)c;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1ModelExchangeLibrary_setTime(JNIEnv*, jobject, jlong p, jlong c, jdouble time)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiSetTimeTYPE* fmiSetTime = fmu->fmiSetTime_;
    return (*fmiSetTime)((void*)c, time);
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1ModelExchangeLibrary_setContinuousStates(JNIEnv* env, jobject, jlong p, jlong c, jdoubleArray x)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    const jsize size = env->GetArrayLength(x);
    jdouble* _x = env->GetDoubleArrayElements(x, nullptr);

    fmiSetContinuousStatesTYPE* fmiSetContinuousStates = fmu->fmiSetContinuousStates_;
    fmiStatus status = (*fmiSetContinuousStates)((void*)c, _x, size);

    env->ReleaseDoubleArrayElements(x, _x, 0);

    return status;
}


JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1ModelExchangeLibrary_getDerivatives(JNIEnv* env, jobject, jlong p, jlong c, jdoubleArray derivatives)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    const jsize size = env->GetArrayLength(derivatives);
    auto _derivatives = (fmiReal*)malloc(sizeof(fmiReal) * size);

    fmiGetDerivativesTYPE* fmiGetDerivatives = fmu->fmiGetDerivatives_;
    fmiStatus status = (*fmiGetDerivatives)((void*)c, _derivatives, size);

    env->SetDoubleArrayRegion(derivatives, 0, size, _derivatives);
    free(_derivatives);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi_jni_Fmi1ModelExchangeLibrary_getEventIndicators(JNIEnv* env, jobject, jlong p, jlong c, jdoubleArray eventIndicators)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    const jsize size = env->GetArrayLength(eventIndicators);
    auto _eventIndicators = (fmiReal*)malloc(sizeof(fmiReal) * size);

    fmiGetEventIndicatorsTYPE* fmiGetEventIndicators = fmu->fmiGetEventIndicators_;
    fmiStatus status = (*fmiGetEventIndicators)((void*)c, _eventIndicators, size);

    env->SetDoubleArrayRegion(eventIndicators, 0, size, _eventIndicators);
    free(_eventIndicators);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1ModelExchangeLibrary_getContinuousStates(JNIEnv* env, jobject, jlong p, jlong c, jdoubleArray x)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    const jsize size = env->GetArrayLength(x);
    auto _x = (fmiReal*)malloc(sizeof(fmiReal) * size);

    fmiGetContinuousStatesTYPE* fmiGetContinuousStates = fmu->fmiGetContinuousStates_;
    fmiStatus status = (*fmiGetContinuousStates)((void*)c, _x, size);

    env->SetDoubleArrayRegion(x, 0, size, _x);
    free(_x);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1ModelExchangeLibrary_getNominalContinuousStates(JNIEnv* env, jobject, jlong p, jlong c, jdoubleArray xNominal)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    const jsize size = env->GetArrayLength(xNominal);
    auto _xNominal = (fmiReal*)malloc(sizeof(fmiReal) * size);

    fmiGetNominalContinuousStatesTYPE* fmiGetNominalContinuousStates = fmu->fmiGetNominalContinuousStates_;
    fmiStatus status = (*fmiGetNominalContinuousStates)((void*)c, _xNominal, size);

    env->SetDoubleArrayRegion(xNominal, 0, size, _xNominal);
    free(_xNominal);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1ModelExchangeLibrary_getStateValueReferences(JNIEnv* env, jobject, jlong p, jlong c, jlongArray vrx)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    const jsize size = env->GetArrayLength(vrx);
    auto _vrx = (jlong*)malloc(sizeof(jlong) * size);

    fmiGetStateValueReferencesTYPE* fmiGetStateValueReferences = fmu->fmiGetStateValueReferences_;
    fmiStatus status = (*fmiGetStateValueReferences)((void*)c, (fmiValueReference*)_vrx, size);

    env->SetLongArrayRegion(vrx, 0, size, _vrx);
    free(_vrx);

    return status;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1ModelExchangeLibrary_terminate(JNIEnv*, jobject, jlong p, jlong c)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiTerminateTYPE* fmiTerminate = fmu->fmiTerminate_;
    return (*fmiTerminate)((void*)c);
}

JNIEXPORT void JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1ModelExchangeLibrary_freeModelInstance(JNIEnv*, jobject, jlong p, jlong c)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiFreeModelInstanceTYPE* fmiFreeInstance = fmu->fmiFreeModelInstance_;
    (*fmiFreeInstance)((void*)c);
}


/***************************************************
Functions for FMI for Co-Simulation
****************************************************/

JNIEXPORT jlong JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1CoSimulationLibrary_instantiateSlave(JNIEnv* env, jobject, jlong p, jstring instanceName, jstring guid, jstring fmuLocation, jboolean loggingOn)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);

    const char* _guid = env->GetStringUTFChars(guid, nullptr);
    const char* _fmuLocation = env->GetStringUTFChars(fmuLocation, nullptr);
    const char* _instanceName = env->GetStringUTFChars(instanceName, nullptr);

    fmiInstantiateSlaveTYPE* fmiInstantiate = fmu->fmiInstantiateSlave_;
    fmiComponent c = (*fmiInstantiate)(_instanceName, _guid, _fmuLocation, "application/x-fmu-sharedlibrary", 0, 0, 0, fmu->csCallback_, (fmiBoolean)loggingOn);

    env->ReleaseStringUTFChars(guid, _guid);
    env->ReleaseStringUTFChars(fmuLocation, _fmuLocation);
    env->ReleaseStringUTFChars(instanceName, _instanceName);

    return (jlong)c;
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1CoSimulationLibrary_initializeSlave(JNIEnv*, jobject, jlong p, jlong c, jdouble startTime, jdouble stopTime)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiBoolean stopTimeDefined = stopTime > startTime;
    fmiInitializeSlaveTYPE* fmiSetup = fmu->fmiInitializeSlave_;
    return (*fmiSetup)((void*)c, startTime, stopTimeDefined, stopTime);
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1CoSimulationLibrary_doStep(JNIEnv*, jobject, jlong p, jlong c, jdouble currentCommunicationPoint, jdouble communicationStepSize, jboolean newStep)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiDoStepTYPE* fmiDoStep = fmu->fmiDoStep_;
    return (*fmiDoStep)((void*)c, currentCommunicationPoint, communicationStepSize, newStep);
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1CoSimulationLibrary_resetSlave(JNIEnv*, jobject, jlong p, jlong c)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiResetSlaveTYPE* fmiReset = fmu->fmiResetSlave_;
    return (*fmiReset)((void*)c);
}

JNIEXPORT jint JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1CoSimulationLibrary_terminateSlave(JNIEnv*, jobject, jlong p, jlong c)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiTerminateSlaveTYPE* fmiTerminate = fmu->fmiTerminateSlave_;
    return (*fmiTerminate)((void*)c);
}

JNIEXPORT void JNICALL Java_no_ntnu_ihb_fmi4j_importer_fmi1_jni_Fmi1CoSimulationLibrary_freeSlaveInstance(JNIEnv*, jobject, jlong p, jlong c)
{
    auto fmu = reinterpret_cast<FmuInstance*>(p);
    fmiFreeSlaveInstanceTYPE* fmiFreeInstance = fmu->fmiFreeSlaveInstance_;
    (*fmiFreeInstance)((void*)c);
}


#ifdef __cplusplus
}
#endif
