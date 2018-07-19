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

package no.mechatronics.sfi.fmu2jar.templates

import no.mechatronics.sfi.fmi4j.modeldescription.CommonModelDescription
import no.mechatronics.sfi.fmi4j.modeldescription.variables.ModelVariables

object CodeGeneration {

    private val licenseHeader: String by lazy {
        CodeGeneration::class.java.classLoader.getResource("license_header.txt").readText(Charsets.UTF_8)
    }

     fun generateWrapper(modelDescription: CommonModelDescription): String {

        val modelName: String = modelDescription.modelName
        val modelVariables: ModelVariables = modelDescription.modelVariables

        return """
$licenseHeader

package no.mechatronics.sfi.fmu2jar.${modelName.toLowerCase()}

import java.net.URL
import no.mechatronics.sfi.fmi4j.importer.Fmu
import no.mechatronics.sfi.fmi4j.common.Real
import no.mechatronics.sfi.fmi4j.common.FmuRead
import no.mechatronics.sfi.fmi4j.common.FmiStatus
import no.mechatronics.sfi.fmi4j.common.FmiSimulation
${modelDescription.supportsModelExchange.let { if (it) "import org.apache.commons.math3.ode.FirstOrderIntegrator" else ""}}

/**
 * Autogenerated file generated by FMU2Jar
 *
 * @author Lars Ivar Hatledal
 */
class $modelName private constructor(
    val fmu: FmiSimulation
) : FmiSimulation by fmu {

    companion object {

        private val fmuFile: Fmu by lazy {
            val url: URL = $modelName::class.java.classLoader.getResource("$modelName.fmu")!!
            Fmu.from(url)
        }
        ${generateNewInstanceMethod(modelDescription)}
    }

    /**
    * Access variables with causality=LOCAL
    */
    val locals = Locals()

    /**
    * Access variables with causality=INPUT
    */
    val inputs = Inputs()

    /**
    * Access variables with causality=OUTPUT
    */
    val outputs = Outputs()

    /**
    * Access variables with causality=PARAMATER
    */
    val parameters = Parameters()

    /**
    * Access variables with causality=CALCULATED_PARAMATER
    */
    val calculatedParameters = CalculatedParameters()

    inner class Inputs internal constructor() {
        ${VariableAccessorsTemplate.generateInputsBody(modelVariables)}
    }

    inner class Outputs internal constructor() {
        ${VariableAccessorsTemplate.generateOutputsBody(modelVariables)}
    }

    inner class Parameters internal constructor() {
        ${VariableAccessorsTemplate.generateParametersBody(modelVariables)}
    }

    inner class CalculatedParameters internal constructor() {
        ${VariableAccessorsTemplate.generateCalculatedParametersBody(modelVariables)}
    }

    inner class Locals internal constructor() {
        ${VariableAccessorsTemplate.generateLocalsBody(modelVariables)}
    }

}

            """

    }

    private fun generateNewInstanceMethod(modelDescription: CommonModelDescription): String {

        val modelName = modelDescription.modelName
        return StringBuilder().apply {

            if (modelDescription.supportsCoSimulation) {
                append(
                        """
        @JvmStatic
        fun newInstance(): $modelName {
            return $modelName(fmuFile.asCoSimulationFmu().newInstance())
        }
            """
                )
            }
            if (modelDescription.supportsModelExchange) {
                append(
                        """
        @JvmStatic
        fun newInstance(solver: FirstOrderIntegrator): $modelName {
            return $modelName(fmuFile.asModelExchangeFmu().newInstance(solver))
        }
            """
                )
            }

        }.toString()

    }

}