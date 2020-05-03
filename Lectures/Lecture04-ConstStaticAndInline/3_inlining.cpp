////////////////////////////////////////////////////////////////////////////////
/// Inlining
///
/// 1) Method invocations are "expensive" from the perspective of assembly code.
///   - Evaluate and prepare all parameters, i.e., pushing onto stack
///   - Jump to new location in instruction memory
///   - Run the method
///   - Prepare the return value
///   - Jump back to calling code and pop return value
/// 2) Inlining is a compiler optimization to "copy-and-paste" the internals of
///    a method at the call location, so that the assumbly code is quicker.
///   - Run the method
/// 3) Inlining inflates the size of compiled code typically so is not always
///    used.
/// 4) While inlining rules are out of scope, understand the following:
///   - The inline keyword is a linker directive and not a note to the compiler
///     to inline.
///   - Define short methods in the class with the declaration. Only these are
///     candidates for inlining. Methods defined in cpp files will not be
///     inlined except within their compilation unit.
///   - Use const regularly, as this is a typical place where inlining can be
///     applied by the compiler.
///   - Inlining may actually slow down, inflate, and add thrashing to a 
///     program.
////////////////////////////////////////////////////////////////////////////////