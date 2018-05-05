/*
 * The MIT License
 *
 * Copyright 2017-2018 Norwegian University of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

package no.mechatronics.sfi.fmi4j.modeldescription

import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlElementWrapper
import com.fasterxml.jackson.dataformat.xml.annotation.JacksonXmlProperty
import no.mechatronics.sfi.fmi4j.modeldescription.misc.SourceFile
import no.mechatronics.sfi.fmi4j.modeldescription.misc.SourceFileImpl
import java.io.Serializable

interface FmuData {

    val modelIdentifier: String
    val needsExecutionTool: Boolean
    val canBeInstantiatedOnlyOncePerProcess: Boolean
    val canNotUseMemoryManagementFunctions: Boolean
    val canGetAndSetFMUstate: Boolean
    val canSerializeFMUstate: Boolean
    val providesDirectionalDerivative: Boolean
    val sourceFiles: List<SourceFile>

}


/**
 * Represents the content within the <CoSimulation></> XML element
 *
 * @author Lars Ivar Hatledal
 */
interface CoSimulationData: FmuData {

    val canHandleVariableCommunicationStepSize: Boolean
    val canInterpolateInputs: Boolean
    val maxOutputDerivativeOrder: Int
    val canRunAsynchronuously: Boolean

}

/**
 * Represents the content within the <ModelExchange></> XML element
 *
 * @author Lars Ivar Hatledal
 */
interface ModelExchangeData: FmuData {

    val completedIntegratorStepNotNeeded: Boolean

}


/**
 * @author Lars Ivar Hatledal
 */
sealed class FmuDataImpl : FmuData, Serializable {

    @JacksonXmlProperty
    override lateinit var modelIdentifier: String

    @JacksonXmlProperty
    override val needsExecutionTool: Boolean = false

    @JacksonXmlProperty
    override val canNotUseMemoryManagementFunctions: Boolean = false

    @JacksonXmlProperty
    override val canGetAndSetFMUstate: Boolean = false

    @JacksonXmlProperty
    override val canSerializeFMUstate: Boolean = false

    @JacksonXmlProperty
    override val providesDirectionalDerivative: Boolean = false

    @JacksonXmlProperty
    override val canBeInstantiatedOnlyOncePerProcess: Boolean = false

    @JacksonXmlElementWrapper(localName = "SourceFiles")
    @JacksonXmlProperty(localName = "File")
    private val _sourceFiles: List<SourceFileImpl>? = null

    override val sourceFiles
        get() = _sourceFiles ?: emptyList()

    override fun toString(): String {
        return "FmuDataImpl{modelIdentifier=$modelIdentifier, needsExecutionTool=$needsExecutionTool, canNotUseMemoryManagementFunctions=$canNotUseMemoryManagementFunctions, canGetAndSetFMUstate=$canGetAndSetFMUstate, canSerializeFMUstate=$canSerializeFMUstate, providesDirectionalDerivative=$providesDirectionalDerivative}"
    }

}

/**
 * @author Lars Ivar Hatledal
 */
internal class CoSimulationDataImpl : FmuDataImpl(), CoSimulationData {

    @JacksonXmlProperty
    override val canHandleVariableCommunicationStepSize: Boolean = false

    @JacksonXmlProperty
    override val canInterpolateInputs: Boolean = false

    @JacksonXmlProperty
    override val maxOutputDerivativeOrder: Int = 0

    @JacksonXmlProperty
    override val canRunAsynchronuously: Boolean = false

    override fun toString(): String {
        return "CoSimulationDataImpl{modelIdentifier=$modelIdentifier, needsExecutionTool=$needsExecutionTool, canHandleVariableCommunicationStepSize=$canHandleVariableCommunicationStepSize, canInterpolateInputs=$canInterpolateInputs, maxOutputDerivativeOrder=$maxOutputDerivativeOrder, canRunAsynchronuously=$canRunAsynchronuously, canBeInstantiatedOnlyOncePerProcess=$canBeInstantiatedOnlyOncePerProcess, canNotUseMemoryManagementFunctions=$canNotUseMemoryManagementFunctions, canGetAndSetFMUstate=$canGetAndSetFMUstate, canSerializeFMUstate=$canSerializeFMUstate, providesDirectionalDerivative=$providesDirectionalDerivative}"
    }

}

/**
 * @author Lars Ivar Hatledal
 */
internal class ModelExchangeDataImpl : FmuDataImpl(), ModelExchangeData {

    @JacksonXmlProperty
    override val completedIntegratorStepNotNeeded: Boolean = false

    override fun toString(): String {
        return "ModelExchangeDataImpl{modelIdentifier=$modelIdentifier, needsExecutionTool=$needsExecutionTool, completedIntegratorStepNotNeeded=$completedIntegratorStepNotNeeded, canBeInstantiatedOnlyOncePerProcess=$canBeInstantiatedOnlyOncePerProcess, canNotUseMemoryManagementFunctions=$canNotUseMemoryManagementFunctions, canGetAndSetFMUstate=$canGetAndSetFMUstate, canSerializeFMUstate=$canSerializeFMUstate, providesDirectionalDerivative=$providesDirectionalDerivative}"
    }

}