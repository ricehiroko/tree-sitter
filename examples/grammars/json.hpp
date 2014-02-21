#ifndef tree_sitter__grammars__json_h
#define tree_sitter__grammars__json_h

#include "tree_sitter/compiler.h"

namespace test_grammars {
    using tree_sitter::Grammar;
    using namespace tree_sitter::rules;
    
    static rule_ptr comma_sep(const rule_ptr &rule) {
        return choice({
            seq({
                rule,
                repeat(seq({ _sym("comma"), rule })),
            }),
            blank(),
        });
    }
    
    Grammar json() {
        return Grammar("value", {
            { "value", choice({
                sym("object"),
                sym("array"),
                sym("string"), 
                sym("number") }) },
            { "object", seq({
                _sym("left_brace"),
                comma_sep(seq({
                    sym("string"),
                    _sym("colon"),
                    sym("value") })),
                _sym("right_brace"), }) },
            { "array", seq({
                _sym("left_bracket"),
                comma_sep(sym("value")),
                _sym("right_bracket"), }) },
            { "string", seq({
                str("\""),
                repeat(choice({
                    pattern("[^\"]"),
                    str("\\\""),
                })),
                str("\"") }) },
            { "number", pattern("\\d+") },
            { "comma", str(",") },
            { "colon", str(":") },
            { "left_bracket", str("[") },
            { "right_bracket", str("]") },
            { "left_brace", str("{") },
            { "right_brace", str("}") },
        });
    }
}

#endif