package no.ntnu.ihb.fmi4j

import no.ntnu.ihb.fmi4j.modeldescription.ModelDescriptionProvider
import no.ntnu.ihb.fmi4j.modeldescription.parser.ModelDescriptionParser
import no.ntnu.ihb.fmi4j.modeldescription.variables.*
import org.gradle.api.Plugin
import org.gradle.api.Project
import org.gradle.api.artifacts.DependencyResolutionListener
import org.gradle.api.artifacts.ResolvableDependencies
import org.gradle.api.provider.Property

class FmuPluginExtension {

    final Property<String> version
    final Property<String> configurationName

    FmuPluginExtension(Project project) {
        version = project.objects.property(String)
        version.set("0.15.2")
        configurationName = project.objects.property(String)
        configurationName.set("implementation")
    }

}

class FmuPlugin implements Plugin<Project> {

    void apply(Project target) {
        def sourceDir = new File(target.projectDir, "src/main/resources/fmus")
        def outputDir = new File(target.buildDir, "generated/fmus")

        target.sourceSets {
            main {
                java {
                    srcDirs += outputDir
                }
            }
        }

        def fmi4j = target.extensions.create('fmi4j', FmuPluginExtension, target)

        target.gradle.addListener(new DependencyResolutionListener(){

            @Override
            void beforeResolve(ResolvableDependencies resolvableDependencies) {
                target.dependencies.add(fmi4j.configurationName.get(), "com.github.NTNU-IHB:FMI4j:${fmi4j.version.get()}")
                target.gradle.removeListener(this)
            }

            @Override
            void afterResolve(ResolvableDependencies dependencies) {}

        })

        def myTask = target.task("generateFMUWrappers") {
            doLast {
                compileSources(sourceDir, outputDir)
            }
        }

        target.afterEvaluate {
            target.tasks['compileJava'].dependsOn myTask
        }

    }


    private void compileSources(File srcDir, File outputDir) {

        if (!srcDir.exists()) {
            throw java.lang.IllegalArgumentException("No such file: '$srcDir'")
        }

        srcDir.listFiles().each { file ->

            if (file.name.toLowerCase().endsWith(".fmu")) {

                def md = ModelDescriptionParser.parse(file)
                def out = new File(outputDir, "no/ntnu/ihb/fmi4j/${md.modelName}.java")
                out.parentFile.mkdirs()
                out.write(new CodeGenerator(md).generateBody())
            }

        }

    }

}

/**
 * @author Lars Ivar Hatledal
 */
class CodeGenerator {

    private String modelName
    private ModelDescriptionProvider md

    CodeGenerator(ModelDescriptionProvider md) {
        this.md = md
        this.modelName = md.modelName
    }

    String generateBody() {

        def solverImport = ""
        if (md.supportsModelExchange) {
            solverImport = "import no.ntnu.ihb.fmi4j.solvers.Solver"
        }

        return """
package no.ntnu.ihb.fmi4j;

import java.net.URL;
import java.io.File;
import java.util.List;
import java.util.Objects;
import java.util.Iterator;
import java.io.IOException;
import no.ntnu.ihb.fmi4j.common.*;
import no.ntnu.ihb.fmi4j.importer.*;
import no.ntnu.ihb.fmi4j.modeldescription.*;
import no.ntnu.ihb.fmi4j.modeldescription.variables.*;
$solverImport

/***
 * Class wrapping FMU named '${modelName}' auto-generated by FmuPlugin
 *
 * @author Lars Ivar Hatledal
 */
public class ${modelName} implements FmuSlave {

    private static Fmu fmu = null;
    private final FmuSlave slave;

    private ${modelName}(FmuSlave slave) {
        this.slave = slave;
    }

    private static Fmu getOrCreateFmu() {
        if (fmu == null) {
            try {
                URL url = ${modelName}.class.getClassLoader().getResource("fmus/${modelName}.fmu");
                fmu = Fmu.from(new File(url.getFile()));
            } catch (IOException ex) {
                throw new RuntimeException();
            }
        }
        return fmu;
    }

    ${generateFactories()}

    @Override
    public CoSimulationModelDescription getModelDescription() {
        return slave.getModelDescription();
    }

    @Override
    public ModelVariables getModelVariables() {
        return slave.getModelVariables();
    }

    @Override
    public FmiStatus getLastStatus() {
        return slave.getLastStatus();
    }

    @Override
    public boolean isTerminated() {
        return slave.isTerminated();
    }

    @Override
    public double getSimulationTime() {
        return slave.getSimulationTime();
    }

    @Override
    public boolean simpleSetup() {
        return simpleSetup(0.0);
    }

    public boolean simpleSetup(double start) {
        return simpleSetup(start, 0.0);
    }

    public boolean simpleSetup(double start, double stop) {
        return simpleSetup(start, stop, 0.0);
    }

    @Override
    public boolean simpleSetup(double start, double stop, double tolerance) {
        return slave.setup(start, stop, tolerance) && slave.enterInitializationMode() && slave.exitInitializationMode();
    }

    @Override
    public boolean setup() {
        return setup(0.0);
    }

    public boolean setup(double start) {
        return setup(start, 0.0);
    }

    public boolean setup(double start, double stop) {
        return setup(start, stop, 0.0);
    }

    @Override
    public boolean setup(double start, double stop, double tolerance) {
        return slave.setup(start, stop, tolerance);
    }

    @Override
    public boolean enterInitializationMode() {
        return slave.enterInitializationMode();
    }

    @Override
    public boolean exitInitializationMode() {
        return slave.exitInitializationMode();
    }

    @Override
    public boolean doStep(double stepSize) {
        return slave.doStep(stepSize);
    }

    @Override
    public boolean cancelStep() {
        return slave.cancelStep();
    }

    @Override
    public boolean terminate() {
        return slave.terminate();
    }

    @Override
    public boolean reset() {
        return slave.reset();
    }

    @Override
    public double[] getDirectionalDerivative(long[] vUnknownRef, long[] vKnownRef, double[] dvKnown) {
        return slave.getDirectionalDerivative(vUnknownRef, vKnownRef, dvKnown);
    }

    @Override
    public long getFMUstate() {
        return slave.getFMUstate();
    }

    @Override
    public boolean setFMUstate(long state) {
        return slave.setFMUstate(state);
    }

    @Override
    public boolean freeFMUstate(long state) {
        return slave.freeFMUstate(state);
    }

    @Override
    public byte[] serializeFMUstate(long state) {
        return slave.serializeFMUstate(state);
    }

    @Override
    public long deSerializeFMUstate(byte[] state) {
        return slave.deSerializeFMUstate(state);
    }

    @Override
    public FmuVariableAccessor getVariableAccessor() {
        return slave.getVariableAccessor();
    }

    @Override
    public void close() {
        slave.close();
    }

    private Locals locals;
    private Inputs inputs;
    private Outputs outputs;
    private Parameters parameters;
    private CalculatedParameters calculatedParameters;

    /**
     * Access variables with causality=LOCAL
     */
    public Locals getLocals() {
        if (locals == null) {
            locals = new Locals();
        }
        return locals;
    }

    /**
     * Access variables with causality=INPUT
     */
    public Inputs getInputs() {
     if (inputs == null) {
            inputs = new Inputs();
        }
        return inputs;
    }

    /**
     * Access variables with causality=OUTPUT
     */
    public Outputs getOutputs() {
     if (outputs == null) {
            outputs = new Outputs();
        }
        return outputs;
    }

    /**
     * Access variables with causality=PARAMETER
     */
    public Parameters getParameters() {
     if (parameters == null) {
            parameters = new Parameters();
        }
        return parameters;
    }

    /**
     * Access variables with causality=CALCULATED_PARAMETER
     */
    public CalculatedParameters getCalculatedParameters() {
     if (calculatedParameters == null) {
            calculatedParameters = new CalculatedParameters();
        }
        return calculatedParameters;
    }

    public class AbstractParameters implements Iterable<TypedScalarVariable<?>> {

        private final List<TypedScalarVariable<?>> vars;

        private AbstractParameters(Causality causality) {
            this.vars = getModelVariables().getByCausality(causality);
        }

        public int size() {
            return vars.size();
        }

        public List<TypedScalarVariable<?>> get() {
            return vars;
        }

        @Override
        public Iterator<TypedScalarVariable<?>> iterator() {
            return vars.iterator();
        }

    }

    public class Inputs extends AbstractParameters {

        private Inputs() {
            super(Causality.INPUT);
        }
        ${generateAccessors(Causality.INPUT)}

    }

    public class Outputs extends AbstractParameters {

        private Outputs() {
            super(Causality.OUTPUT);
        }
        ${generateAccessors(Causality.OUTPUT)}

    }

    public class Parameters extends AbstractParameters {

        private Parameters() {
            super(Causality.PARAMETER);
        }
        ${generateAccessors(Causality.PARAMETER)}

    }

    public class CalculatedParameters extends AbstractParameters {

        private CalculatedParameters() {
            super(Causality.CALCULATED_PARAMETER);
        }
        ${generateAccessors(Causality.CALCULATED_PARAMETER)}

    }

    public class Locals extends AbstractParameters {

        private Locals() {
            super(Causality.LOCAL);
        }
        ${generateAccessors(Causality.LOCAL)}

    }

}

"""

    }

    private String generateFactories() {

        def result = ""
        if (md.supportsCoSimulation) {
            result += """

            public static ${modelName} newInstance() {
                FmuSlave slave = getOrCreateFmu().asCoSimulationFmu().newInstance();
                return new ${modelName}(Objects.requireNonNull(slave));
            }
            """

        }

        if (md.supportsModelExchange) {

            result += """

            public static ${modelName} newInstance(Solver solver) {
                FmuSlave slave = getOrCreateFmu().asModelExchangeFmu(solver).newInstance()
                return new ${modelName}(Objects.requireNonNull(slave));
            }
            """

        }

        return result

    }

    private String generateAccessors(Causality causality) {

        def sb = new StringBuilder()

            sb.append("\n")

            md.modelVariables.getByCausality(causality).each { v ->

                if (!v.name.contains("[")) {

                    def functionName = v.name.replace(".", "_").uncapitalize()

                    sb.append("""
                    ${generateJavaDoc(v)}
                    public ${v.typeName}Variable $functionName() {
                        return slave.getModelDescription().getModelVariables().getByName("${v.name}").as${v.typeName}Variable();
                    }
                    
                    """)

                }


            }

        return sb.toString()

    }

    private String generateJavaDoc(TypedScalarVariable v) {

        def star = " *"
        def newLine = "\n$star\n"
        def sb = new StringBuilder()

        sb.append("\n")
        sb.append("/**\n")
        sb.append("$star ").append("Name:").append(v.name)

        if (v.declaredType != null) {
            sb.append(newLine).append("$star DeclaredType=$v.declaredType")
        }
        if (v.start != null) {
            sb.append(newLine).append("$star Start=$v.start")
        }
        if (v.causality != null) {
            sb.append(newLine).append("$star Causality=$v.causality")
        }
        if (v.variability != null) {
            sb.append(newLine).append("$star Variability=$v.variability")
        }
        if (v.initial != null) {
            sb.append(newLine).append("$star Initial=$v.initial")
        }

        if (v instanceof IntegerVariable) {
            if (v.min != null) {
                sb.append(newLine).append("$star min=$v.min")
            }
            if (v.max != null) {
                sb.append(newLine).append("$star max=$v.max")
            }
            if (v.quantity != null) {
                sb.append(newLine).append("$star quantity=$v.quantity")
            }
        } else if (v instanceof RealVariable) {
            if (v.min != null) {
                sb.append(newLine).append("$star min=$v.min")
            }
            if (v.max != null) {
                sb.append(newLine).append("$star max=$v.max")
            }
            if (v.quantity != null) {
                sb.append(newLine).append("$star quantity=$v.quantity")
            }
        } else if (v instanceof EnumerationVariable) {
             if (v.min != null) {
                 sb.append(newLine).append("$star min=$v.min")
             }
             if (v.max != null) {
                 sb.append(newLine).append("$star max=$v.max")
             }
             if (v.quantity != null) {
                 sb.append(newLine).append("$star quantity=$v.quantity")
             }
        }


        if (v.description != null) {
            sb.append(newLine).append("$star Description=$v.description")
        }

        sb.append("\n */")

        return sb.toString()

    }

}

