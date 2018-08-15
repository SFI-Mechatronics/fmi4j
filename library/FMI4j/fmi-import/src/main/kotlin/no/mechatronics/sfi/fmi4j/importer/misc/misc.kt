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

package no.mechatronics.sfi.fmi4j.importer.misc

import no.mechatronics.sfi.fmi4j.jni.PointerByReference

/**
 *
 * @author Lars Ivar Hatledal
 */
class FmuState : PointerByReference()

/**
 *
 * @author Lars Ivar Hatledal
 */
internal class ArrayBuffers {

    val vr = IntArray(1)
    val iv = IntArray(1)
    val rv = DoubleArray(1)
    val bv = BooleanArray(1)
    val sv = arrayOf("")

}

/**
 *
 * @author Lars Ivar Hatledal
 */
class DirectionalDerivatives(
        size: Int
) {

    val vUnknownRef = IntArray(size)
    val vKnownRef = IntArray(size)
    val dvKnown = DoubleArray(size)
    val dvUnknown = DoubleArray(size)

}

///**
// * https://stackoverflow.com/questions/29162569/jna-passing-string-by-reference-to-dll-but-non-return
// */
//class StringByReference : ByReference {
//
//    var value: String
//        get() = pointer.getString(0)
//        set(str) = pointer.setString(0, str)
//
//    @JvmOverloads constructor(size: Int = 0) : super(if (size < 4) 4 else size) {
//        pointer.clear((if (size < 4) 4 else size).toLong())
//    }
//
//}
