// A Bison parser, made by GNU Bison 3.6.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 4 "parser.y"

#define YYSTYPE void *
using namespace ast;

#line 46 "yacc_bison.h"




# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

namespace yy {
#line 177 "yacc_bison.h"




  /// A Bison parser.
  class parser
  {
  public:
#ifndef YYSTYPE
    /// Symbol semantic values.
    typedef int semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    ///yylex interface
  const Token* current_token;  virtual int yylex(void**) = 0;
    virtual void access_ast(void*) = 0;
 /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 613,                 // error
    YYUNDEF = 614,                 // "invalid token"
    KEYWORD = 1,                   // KEYWORD
    STR = 2,                       // STR
    CHAR = 3,                      // CHAR
    REAL = 4,                      // REAL
    INT = 5,                       // INT
    BOOL = 6,                      // BOOL
    IDENT = 7,                     // IDENT
    NULLPTR = 9,                   // NULLPTR
    ERRORTOKEN = 10,               // ERRORTOKEN
    COMMENT = 11,                  // COMMENT
    LENGTH = 12,                   // LENGTH
    KEYWORD_PROGRAM = 256,         // KEYWORD_PROGRAM
    KEYWORD_CONST = 257,           // KEYWORD_CONST
    KEYWORD_VAR = 258,             // KEYWORD_VAR
    KEYWORD_PROCEDURE = 259,       // KEYWORD_PROCEDURE
    KEYWORD_FUNCTION = 260,        // KEYWORD_FUNCTION
    KEYWORD_BEGIN = 261,           // KEYWORD_BEGIN
    KEYWORD_END = 262,             // KEYWORD_END
    KEYWORD_ARRAY = 263,           // KEYWORD_ARRAY
    KEYWORD_INTEGER = 264,         // KEYWORD_INTEGER
    KEYWORD_REAL = 265,            // KEYWORD_REAL
    KEYWORD_BOOLEAN = 266,         // KEYWORD_BOOLEAN
    KEYWORD_CHAR = 267,            // KEYWORD_CHAR
    KEYWORD_IF = 268,              // KEYWORD_IF
    KEYWORD_THEN = 269,            // KEYWORD_THEN
    KEYWORD_ELSE = 270,            // KEYWORD_ELSE
    KEYWORD_FOR = 271,             // KEYWORD_FOR
    KEYWORD_TO = 272,              // KEYWORD_TO
    KEYWORD_DO = 273,              // KEYWORD_DO
    KEYWORD_OF = 274,              // KEYWORD_OF
    KEYWORD_DIV = 275,             // KEYWORD_DIV
    KEYWORD_MOD = 276,             // KEYWORD_MOD
    KEYWORD_AND = 277,             // KEYWORD_AND
    KEYWORD_OR = 278,              // KEYWORD_OR
    KEYWORD_NOT = 279,             // KEYWORD_NOT
    KEYWORD_READ = 280,            // KEYWORD_READ
    KEYWORD_WRITE = 281,           // KEYWORD_WRITE
    KEYWORD_LENGTH = 282,          // KEYWORD_LENGTH
    MARKER_RANGE = 512,            // MARKER_RANGE
    MARKER_LOGICNOT = 513,         // MARKER_LOGICNOT
    MARKER_NEQ = 529,              // MARKER_NEQ
    MARKER_LE = 530,               // MARKER_LE
    MARKER_GE = 531,               // MARKER_GE
    MARKER_LT = 532,               // MARKER_LT
    MARKER_EQ = 533,               // MARKER_EQ
    MARKER_GT = 534,               // MARKER_GT
    MARKER_ADD = 544,              // MARKER_ADD
    MARKER_SUB = 545,              // MARKER_SUB
    MARKER_LOGICOR = 546,          // MARKER_LOGICOR
    MARKER_MUL = 560,              // MARKER_MUL
    MARKER_DIV = 561,              // MARKER_DIV
    MARKER_MOD = 562,              // MARKER_MOD
    MARKER_LOGICAND = 563,         // MARKER_LOGICAND
    MARKER_LPAREN = 576,           // MARKER_LPAREN
    MARKER_RPAREN = 577,           // MARKER_RPAREN
    MARKER_LBRACKET = 592,         // MARKER_LBRACKET
    MARKER_RBRACKET = 593,         // MARKER_RBRACKET
    MARKER_ASSIGN = 608,           // MARKER_ASSIGN
    MARKER_COMMA = 609,            // MARKER_COMMA
    MARKER_DOT = 610,              // MARKER_DOT
    MARKER_SEMICOLON = 611,        // MARKER_SEMICOLON
    MARKER_COLON = 612             // MARKER_COLON
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 65, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_KEYWORD = 3,                           // KEYWORD
        S_STR = 4,                               // STR
        S_CHAR = 5,                              // CHAR
        S_REAL = 6,                              // REAL
        S_INT = 7,                               // INT
        S_BOOL = 8,                              // BOOL
        S_IDENT = 9,                             // IDENT
        S_NULLPTR = 10,                          // NULLPTR
        S_ERRORTOKEN = 11,                       // ERRORTOKEN
        S_COMMENT = 12,                          // COMMENT
        S_LENGTH = 13,                           // LENGTH
        S_KEYWORD_PROGRAM = 14,                  // KEYWORD_PROGRAM
        S_KEYWORD_CONST = 15,                    // KEYWORD_CONST
        S_KEYWORD_VAR = 16,                      // KEYWORD_VAR
        S_KEYWORD_PROCEDURE = 17,                // KEYWORD_PROCEDURE
        S_KEYWORD_FUNCTION = 18,                 // KEYWORD_FUNCTION
        S_KEYWORD_BEGIN = 19,                    // KEYWORD_BEGIN
        S_KEYWORD_END = 20,                      // KEYWORD_END
        S_KEYWORD_ARRAY = 21,                    // KEYWORD_ARRAY
        S_KEYWORD_INTEGER = 22,                  // KEYWORD_INTEGER
        S_KEYWORD_REAL = 23,                     // KEYWORD_REAL
        S_KEYWORD_BOOLEAN = 24,                  // KEYWORD_BOOLEAN
        S_KEYWORD_CHAR = 25,                     // KEYWORD_CHAR
        S_KEYWORD_IF = 26,                       // KEYWORD_IF
        S_KEYWORD_THEN = 27,                     // KEYWORD_THEN
        S_KEYWORD_ELSE = 28,                     // KEYWORD_ELSE
        S_KEYWORD_FOR = 29,                      // KEYWORD_FOR
        S_KEYWORD_TO = 30,                       // KEYWORD_TO
        S_KEYWORD_DO = 31,                       // KEYWORD_DO
        S_KEYWORD_OF = 32,                       // KEYWORD_OF
        S_KEYWORD_DIV = 33,                      // KEYWORD_DIV
        S_KEYWORD_MOD = 34,                      // KEYWORD_MOD
        S_KEYWORD_AND = 35,                      // KEYWORD_AND
        S_KEYWORD_OR = 36,                       // KEYWORD_OR
        S_KEYWORD_NOT = 37,                      // KEYWORD_NOT
        S_KEYWORD_READ = 38,                     // KEYWORD_READ
        S_KEYWORD_WRITE = 39,                    // KEYWORD_WRITE
        S_KEYWORD_LENGTH = 40,                   // KEYWORD_LENGTH
        S_MARKER_RANGE = 41,                     // MARKER_RANGE
        S_MARKER_LOGICNOT = 42,                  // MARKER_LOGICNOT
        S_MARKER_NEQ = 43,                       // MARKER_NEQ
        S_MARKER_LE = 44,                        // MARKER_LE
        S_MARKER_GE = 45,                        // MARKER_GE
        S_MARKER_LT = 46,                        // MARKER_LT
        S_MARKER_EQ = 47,                        // MARKER_EQ
        S_MARKER_GT = 48,                        // MARKER_GT
        S_MARKER_ADD = 49,                       // MARKER_ADD
        S_MARKER_SUB = 50,                       // MARKER_SUB
        S_MARKER_LOGICOR = 51,                   // MARKER_LOGICOR
        S_MARKER_MUL = 52,                       // MARKER_MUL
        S_MARKER_DIV = 53,                       // MARKER_DIV
        S_MARKER_MOD = 54,                       // MARKER_MOD
        S_MARKER_LOGICAND = 55,                  // MARKER_LOGICAND
        S_MARKER_LPAREN = 56,                    // MARKER_LPAREN
        S_MARKER_RPAREN = 57,                    // MARKER_RPAREN
        S_MARKER_LBRACKET = 58,                  // MARKER_LBRACKET
        S_MARKER_RBRACKET = 59,                  // MARKER_RBRACKET
        S_MARKER_ASSIGN = 60,                    // MARKER_ASSIGN
        S_MARKER_COMMA = 61,                     // MARKER_COMMA
        S_MARKER_DOT = 62,                       // MARKER_DOT
        S_MARKER_SEMICOLON = 63,                 // MARKER_SEMICOLON
        S_MARKER_COLON = 64,                     // MARKER_COLON
        S_YYACCEPT = 65,                         // $accept
        S_programstruct = 66,                    // programstruct
        S_dot = 67,                              // dot
        S_program_head = 68,                     // program_head
        S_program = 69,                          // program
        S_program_body = 70,                     // program_body
        S_idlist = 71,                           // idlist
        S_const_declarations = 72,               // const_declarations
        S_const = 73,                            // const
        S_const_declaration = 74,                // const_declaration
        S_eq = 75,                               // eq
        S_const_value = 76,                      // const_value
        S_bool = 77,                             // bool
        S_num = 78,                              // num
        S_char = 79,                             // char
        S_add = 80,                              // add
        S_sub = 81,                              // sub
        S_var_declarations = 82,                 // var_declarations
        S_var_declaration = 83,                  // var_declaration
        S_type = 84,                             // type
        S_array = 85,                            // array
        S_of = 86,                               // of
        S_basic_type = 87,                       // basic_type
        S_integer = 88,                          // integer
        S_real = 89,                             // real
        S_boolean = 90,                          // boolean
        S_period = 91,                           // period
        S_range = 92,                            // range
        S_subprogram_declarations = 93,          // subprogram_declarations
        S_subprogram = 94,                       // subprogram
        S_subprogram_head = 95,                  // subprogram_head
        S_procedure = 96,                        // procedure
        S_function = 97,                         // function
        S_formal_parameter = 98,                 // formal_parameter
        S_parameter_list = 99,                   // parameter_list
        S_parameter = 100,                       // parameter
        S_var = 101,                             // var
        S_colon = 102,                           // colon
        S_subprogram_body = 103,                 // subprogram_body
        S_compound_statement = 104,              // compound_statement
        S_begin = 105,                           // begin
        S_end = 106,                             // end
        S_statement_list = 107,                  // statement_list
        S_semicolon = 108,                       // semicolon
        S_statement = 109,                       // statement
        S_for = 110,                             // for
        S_to = 111,                              // to
        S_do = 112,                              // do
        S_assign = 113,                          // assign
        S_if = 114,                              // if
        S_then = 115,                            // then
        S_else = 116,                            // else
        S_variable_list = 117,                   // variable_list
        S_variable = 118,                        // variable
        S_id_varpart = 119,                      // id_varpart
        S_lbracket = 120,                        // lbracket
        S_rbracket = 121,                        // rbracket
        S_procedure_call = 122,                  // procedure_call
        S_lparen = 123,                          // lparen
        S_rparen = 124,                          // rparen
        S_id = 125,                              // id
        S_expression_list = 126,                 // expression_list
        S_comma = 127,                           // comma
        S_expression = 128,                      // expression
        S_simple_expression = 129,               // simple_expression
        S_term = 130,                            // term
        S_factor = 131,                          // factor
        S_not = 132,                             // not
        S_unimus = 133,                          // unimus
        S_addop = 134,                           // addop
        S_mulop = 135,                           // mulop
        S_relop = 136                            // relop
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value (std::move (that.value))
      {}
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);
      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    YY_RVREF (semantic_type) v);

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {};

    /// Build a parser object.
    parser ();
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0




  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const unsigned char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 256,     ///< Last index in yytable_.
      yynnts_ = 72,  ///< Number of nonterminal symbols.
      yyfinal_ = 7 ///< Termination state number.
    };



  };


} // yy
#line 923 "yacc_bison.h"









#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 1003 "yacc_bison.h"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}

  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 84 "parser.y"
                                                        {
  yylhs.value = new ast::Program((ProgramHead*)yystack_[3].value, (ProgramBody*)yystack_[1].value);
  access_ast(yylhs.value);
  //printf("finish!\n");
 }
#line 1457 "yacc_bison.h"
    break;

  case 3:
#line 93 "parser.y"
               {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
 }
#line 1465 "yacc_bison.h"
    break;

  case 4:
#line 99 "parser.y"
                                {
  yylhs.value = new ProgramHead((const ExpKeyword*)yystack_[4].value, new Ident((const Identifier*)yystack_[3].value), (IdentList*)yystack_[1].value);
}
#line 1473 "yacc_bison.h"
    break;

  case 5:
#line 102 "parser.y"
            {
  yylhs.value = new ProgramHead((const ExpKeyword*)yystack_[1].value, new Ident((const Identifier*)yystack_[0].value));
}
#line 1481 "yacc_bison.h"
    break;

  case 6:
#line 105 "parser.y"
                          {
    IdentList* idlist = new IdentList();
  ast::copy_pos_with_check(idlist, (ExpMarker*)yystack_[1].value);
  ast::copy_pos_with_check(idlist, (ExpMarker*)yystack_[0].value);
  yylhs.value = new ProgramHead((const ExpKeyword*)yystack_[3].value, new Ident((const Identifier*)yystack_[2].value), idlist);
}
#line 1492 "yacc_bison.h"
    break;

  case 7:
#line 111 "parser.y"
                                {

    pascal_s::Pos* pos = ((Node*)yystack_[3].value)->visit_pos();

    #define cur_node (reinterpret_cast<const ast::ExpKeyword*>(yystack_[3].value))
    printf("\n program head failed at line:%d column:%d: expect: %s but got error Token\n", pos->line-1, pos->column, convertToString(cur_node->value).c_str());
    #undef  cur_node

    yyerrok;
}
#line 1507 "yacc_bison.h"
    break;

  case 8:
#line 126 "parser.y"
                       {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 1515 "yacc_bison.h"
    break;

  case 9:
#line 131 "parser.y"
                                                                                              {
  yylhs.value = new ProgramBody((ConstDecls*)yystack_[3].value, (VarDecls*)yystack_[2].value, (SubprogramDecls*)yystack_[1].value, (CompoundStatement*)yystack_[0].value);
}
#line 1523 "yacc_bison.h"
    break;

  case 10:
#line 137 "parser.y"
                 {
  yylhs.value = yystack_[2].value;
  ((IdentList*)yylhs.value)->idents.push_back((Identifier*)yystack_[0].value);
  ast::copy_pos_with_check((IdentList*)yylhs.value, (Identifier*)yystack_[0].value);
}
#line 1533 "yacc_bison.h"
    break;

  case 11:
#line 142 "parser.y"
          {
  yylhs.value = new IdentList();
  ((IdentList*)yylhs.value)->idents.push_back((Identifier*)yystack_[0].value);
  ast::copy_pos_with_check((IdentList*)yylhs.value, (Identifier*)yystack_[0].value);
}
#line 1543 "yacc_bison.h"
    break;

  case 12:
#line 151 "parser.y"
                                  {
  yylhs.value = yystack_[1].value;
}
#line 1551 "yacc_bison.h"
    break;

  case 13:
#line 154 "parser.y"
                                        { yylhs.value = nullptr; }
#line 1557 "yacc_bison.h"
    break;

  case 14:
#line 159 "parser.y"
                   {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 1565 "yacc_bison.h"
    break;

  case 15:
#line 165 "parser.y"
                                              {
  yylhs.value = yystack_[4].value;
  ConstDecl* constDecl = new ConstDecl((const Identifier*)yystack_[2].value, (Exp*)yystack_[0].value);
  ((ConstDecls*)yylhs.value)->decls.push_back(constDecl);
}
#line 1575 "yacc_bison.h"
    break;

  case 16:
#line 170 "parser.y"
                    {
  ConstDecl* constDecl = new ConstDecl((const Identifier*)yystack_[2].value, (Exp*)yystack_[0].value);
  yylhs.value = new ConstDecls();
  ((ConstDecls*)yylhs.value)->decls.push_back(constDecl);
}
#line 1585 "yacc_bison.h"
    break;

  case 17:
#line 177 "parser.y"
             {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 1593 "yacc_bison.h"
    break;

  case 18:
#line 183 "parser.y"
          {yylhs.value = new UnExp((const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);}
#line 1599 "yacc_bison.h"
    break;

  case 19:
#line 184 "parser.y"
          {yylhs.value = new UnExp((const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);}
#line 1605 "yacc_bison.h"
    break;

  case 20:
#line 185 "parser.y"
          {yylhs.value = yystack_[0].value;}
#line 1611 "yacc_bison.h"
    break;

  case 21:
#line 186 "parser.y"
          {yylhs.value = yystack_[0].value;}
#line 1617 "yacc_bison.h"
    break;

  case 22:
#line 187 "parser.y"
          {yylhs.value = yystack_[0].value;}
#line 1623 "yacc_bison.h"
    break;

  case 23:
#line 190 "parser.y"
         {yylhs.value = new ExpConstantBoolean(((const ConstantBoolean*)(yystack_[0].value)));}
#line 1629 "yacc_bison.h"
    break;

  case 24:
#line 192 "parser.y"
        {
  yylhs.value = new ExpConstantInteger(((const ConstantInteger*)(yystack_[0].value)));
}
#line 1637 "yacc_bison.h"
    break;

  case 25:
#line 195 "parser.y"
       {
  yylhs.value = new ExpConstantReal(((const ConstantReal*)(yystack_[0].value)));
  }
#line 1645 "yacc_bison.h"
    break;

  case 26:
#line 200 "parser.y"
          {
  yylhs.value = new ExpConstantChar(((const ConstantChar*)(yystack_[0].value)));
}
#line 1653 "yacc_bison.h"
    break;

  case 27:
#line 205 "parser.y"
               {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 1661 "yacc_bison.h"
    break;

  case 28:
#line 210 "parser.y"
               {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 1669 "yacc_bison.h"
    break;

  case 29:
#line 215 "parser.y"
                               { yylhs.value = nullptr;  /* new ExpVoid(); */ }
#line 1675 "yacc_bison.h"
    break;

  case 30:
#line 216 "parser.y"
                               {
  yylhs.value = yystack_[1].value;
}
#line 1683 "yacc_bison.h"
    break;

  case 31:
#line 219 "parser.y"
        {
    printf("\n var declarations parse failed\n");
    yyerrok;
}
#line 1692 "yacc_bison.h"
    break;

  case 32:
#line 227 "parser.y"
                                              {
  yylhs.value = yystack_[4].value;
  VarDecl* vdecl = new VarDecl((IdentList*)yystack_[2].value, (TypeSpec*)yystack_[0].value);
  ((VarDecls*)yylhs.value)->decls.push_back(vdecl);
  ast::copy_pos_with_check((VarDecls*)yylhs.value, vdecl);
}
#line 1703 "yacc_bison.h"
    break;

  case 33:
#line 233 "parser.y"
                    {
  yylhs.value = new VarDecls();

  VarDecl* vdecl = new VarDecl((IdentList*)yystack_[2].value, (TypeSpec*)yystack_[0].value);
  ast::copy_pos_with_check((VarDecls*)yylhs.value, (IdentList*)yystack_[2].value);
  ((VarDecls*)yylhs.value)->decls.push_back(vdecl);
  ast::copy_pos_with_check((VarDecls*)yylhs.value, vdecl);
}
#line 1716 "yacc_bison.h"
    break;

  case 34:
#line 241 "parser.y"
                               {

  // printf(" \n\n test error -------------------------- %s\n", convertToString((Token*)(current_token)).c_str());
    // errors.push_back(new PascalSParseError("test"));
    // printf("\n var declaration failed at line:%d column:%d: expect:array type but got error Token\n", pos->line,pos->column+pos->length+1);

    yyerrok;
}
#line 1729 "yacc_bison.h"
    break;

  case 35:
#line 252 "parser.y"
                     {
  yylhs.value = yystack_[0].value;
}
#line 1737 "yacc_bison.h"
    break;

  case 36:
#line 255 "parser.y"
                                                       {
  yylhs.value = yystack_[3].value;
  ((ArrayTypeSpec*)yylhs.value)->keyword = ((BasicTypeSpec*)yystack_[0].value)->keyword;
  ast::copy_pos_with_check((ArrayTypeSpec*)yylhs.value, ((BasicTypeSpec*)yystack_[0].value)->keyword);
}
#line 1747 "yacc_bison.h"
    break;

  case 37:
#line 262 "parser.y"
                   {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 1755 "yacc_bison.h"
    break;

  case 38:
#line 267 "parser.y"
             {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 1763 "yacc_bison.h"
    break;

  case 39:
#line 273 "parser.y"
                  {yylhs.value = yystack_[0].value;}
#line 1769 "yacc_bison.h"
    break;

  case 40:
#line 274 "parser.y"
                {yylhs.value = yystack_[0].value;}
#line 1775 "yacc_bison.h"
    break;

  case 41:
#line 275 "parser.y"
                   {yylhs.value = yystack_[0].value;}
#line 1781 "yacc_bison.h"
    break;

  case 42:
#line 276 "parser.y"
                {yylhs.value = yystack_[0].value;}
#line 1787 "yacc_bison.h"
    break;

  case 43:
#line 279 "parser.y"
                       {
  yylhs.value = new BasicTypeSpec((const Keyword *)(yystack_[0].value));
}
#line 1795 "yacc_bison.h"
    break;

  case 44:
#line 284 "parser.y"
                 {
  yylhs.value = new BasicTypeSpec((const Keyword *)(yystack_[0].value));
}
#line 1803 "yacc_bison.h"
    break;

  case 45:
#line 289 "parser.y"
                 {
  yylhs.value = new BasicTypeSpec((const Keyword *)(yystack_[0].value));
}
#line 1811 "yacc_bison.h"
    break;

  case 46:
#line 294 "parser.y"
                       {
  yylhs.value = new BasicTypeSpec((const Keyword *)(yystack_[0].value));
}
#line 1819 "yacc_bison.h"
    break;

  case 47:
#line 300 "parser.y"
                                  {
  yylhs.value = yystack_[4].value;
  ((ArrayTypeSpec*)yylhs.value)->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)yystack_[2].value)->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)yystack_[0].value)->value)->attr)));
}
#line 1828 "yacc_bison.h"
    break;

  case 48:
#line 304 "parser.y"
                                   {
  yylhs.value = new ArrayTypeSpec(nullptr);
  ((ArrayTypeSpec*)yylhs.value)->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)yystack_[2].value)->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)yystack_[0].value)->value)->attr)));
}
#line 1837 "yacc_bison.h"
    break;

  case 49:
#line 308 "parser.y"
        {
    printf(" test error %s\n", convertToString((Token*)(current_token)).c_str());
    // new PascalSParseError("pascal S parser Errorr test");

    /* #define cur_node (reinterpret_cast<const ast::ExpMarker*>($3)) */
    /* printf("\nperiod parse failed at line:%d column:%d: expect: num but got %s\n", pos->line,pos->column+pos->length+1,convertToString(cur_node->value).c_str()); */
    /* #undef  cur_node */

    yyerrok;
}
#line 1852 "yacc_bison.h"
    break;

  case 50:
#line 319 "parser.y"
                   {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 1860 "yacc_bison.h"
    break;

  case 51:
#line 324 "parser.y"
                                              {
  if( yystack_[2].value == nullptr ){
    yylhs.value = new SubprogramDecls();
  }else{
    yylhs.value = yystack_[2].value;
  }
  ((SubprogramDecls*)yylhs.value)->subprogram.push_back(((Subprogram*)yystack_[1].value));
}
#line 1873 "yacc_bison.h"
    break;

  case 52:
#line 332 "parser.y"
  { yylhs.value = nullptr;  }
#line 1879 "yacc_bison.h"
    break;

  case 53:
#line 337 "parser.y"
                                          {
  yylhs.value = new Subprogram((SubprogramHead*)yystack_[2].value, (SubprogramBody*)yystack_[0].value);
}
#line 1887 "yacc_bison.h"
    break;

  case 54:
#line 344 "parser.y"
                                {
  yylhs.value = new SubprogramHead((const Keyword*)yystack_[2].value, (const Identifier*)yystack_[1].value, (ParamList*)yystack_[0].value, nullptr);
}
#line 1895 "yacc_bison.h"
    break;

  case 55:
#line 347 "parser.y"
                                                 {
  yylhs.value = new SubprogramHead((const Keyword*)yystack_[4].value, (const Identifier*)yystack_[3].value, (ParamList*)yystack_[2].value, (BasicTypeSpec*)yystack_[0].value);
}
#line 1903 "yacc_bison.h"
    break;

  case 56:
#line 352 "parser.y"
                            {
  // $$ = new ExpKeyword((const Keyword *)($1));
  yylhs.value = yystack_[0].value;
}
#line 1912 "yacc_bison.h"
    break;

  case 57:
#line 358 "parser.y"
                         {
  //$$ = new ExpKeyword((const Keyword *)($1));
  yylhs.value = yystack_[0].value;
}
#line 1921 "yacc_bison.h"
    break;

  case 58:
#line 364 "parser.y"
                  { yylhs.value =  nullptr; /* new ParamList(); */  }
#line 1927 "yacc_bison.h"
    break;

  case 59:
#line 365 "parser.y"
                               {
  yylhs.value = yystack_[1].value;
}
#line 1935 "yacc_bison.h"
    break;

  case 60:
#line 374 "parser.y"
                                     {
  yylhs.value = yystack_[2].value;
  ((ParamList*)yylhs.value)->params.push_back((ParamSpec*)yystack_[0].value);
  ast::copy_pos_with_check((ParamList*)yylhs.value, (ParamSpec*)yystack_[0].value);
}
#line 1945 "yacc_bison.h"
    break;

  case 61:
#line 379 "parser.y"
                                {
  yylhs.value = new ParamList();
  ((ParamList*)yylhs.value)->params.push_back((ParamSpec*)yystack_[0].value);
  ast::copy_pos_with_check((ParamList*)yylhs.value, (ParamSpec*)yystack_[0].value);
  }
#line 1955 "yacc_bison.h"
    break;

  case 62:
#line 389 "parser.y"
                                    {
  yylhs.value = new ParamSpec((const Keyword*)yystack_[3].value, (IdentList*)yystack_[2].value, (TypeSpec*)yystack_[0].value);
}
#line 1963 "yacc_bison.h"
    break;

  case 63:
#line 392 "parser.y"
                                {
  yylhs.value = new ParamSpec(nullptr, (IdentList*)yystack_[2].value, (TypeSpec*)yystack_[0].value);
}
#line 1971 "yacc_bison.h"
    break;

  case 64:
#line 398 "parser.y"
               {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 1979 "yacc_bison.h"
    break;

  case 65:
#line 404 "parser.y"
                   {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 1987 "yacc_bison.h"
    break;

  case 66:
#line 409 "parser.y"
                                                        {
  yylhs.value = new SubprogramBody((ConstDecls*)yystack_[2].value, (VarDecls*)yystack_[1].value, (CompoundStatement*)yystack_[0].value);
}
#line 1995 "yacc_bison.h"
    break;

  case 67:
#line 414 "parser.y"
                                { yylhs.value = nullptr; }
#line 2001 "yacc_bison.h"
    break;

  case 68:
#line 415 "parser.y"
                                   {
  yylhs.value = new CompoundStatement((StatementList*)yystack_[1].value);
}
#line 2009 "yacc_bison.h"
    break;

  case 69:
#line 423 "parser.y"
                   {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2017 "yacc_bison.h"
    break;

  case 70:
#line 428 "parser.y"
               {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
             }
#line 2025 "yacc_bison.h"
    break;

  case 71:
#line 434 "parser.y"
                                       {
  yylhs.value = yystack_[2].value;
  if( yystack_[0].value != nullptr ){
    ((StatementList*)yylhs.value)->statement.push_back((Statement*)yystack_[0].value);
    ast::copy_pos_with_check((StatementList*)yylhs.value, (Statement*)yystack_[0].value);
  }
}
#line 2037 "yacc_bison.h"
    break;

  case 72:
#line 441 "parser.y"
            {
  yylhs.value = new StatementList();
  if( yystack_[0].value != nullptr ){
    ((StatementList*)yylhs.value)->statement.push_back((Statement*)yystack_[0].value);
    ast::copy_pos_with_check((StatementList*)yylhs.value, (Statement*)yystack_[0].value);
  }
}
#line 2049 "yacc_bison.h"
    break;

  case 73:
#line 451 "parser.y"
                           {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2057 "yacc_bison.h"
    break;

  case 74:
#line 456 "parser.y"
                                                      {yylhs.value = new ExecStatement(new ExpAssign((Variable*)yystack_[2].value, (Exp*)yystack_[0].value));}
#line 2063 "yacc_bison.h"
    break;

  case 75:
#line 457 "parser.y"
                                                      {yylhs.value = new ExecStatement((Exp*)yystack_[0].value);}
#line 2069 "yacc_bison.h"
    break;

  case 76:
#line 458 "parser.y"
                                                      {yylhs.value = yystack_[0].value;}
#line 2075 "yacc_bison.h"
    break;

  case 77:
#line 460 "parser.y"
                                      {
                                        yylhs.value = new IfElseStatement((Exp*)yystack_[4].value, (Statement*)yystack_[2].value, (Statement*)yystack_[0].value);
                                        ast::copy_pos_between_tokens((IfElseStatement*)yylhs.value, (ExpKeyword*)yystack_[5].value, (Statement*)yystack_[0].value);
                                      }
#line 2084 "yacc_bison.h"
    break;

  case 78:
#line 465 "parser.y"
{
  yylhs.value = new IfElseStatement((Exp*)yystack_[2].value, (Statement*)yystack_[0].value, nullptr);
  ast::copy_pos_between_tokens((IfElseStatement*)yylhs.value, (ExpKeyword*)yystack_[3].value, (Statement*)yystack_[0].value);
}
#line 2093 "yacc_bison.h"
    break;

  case 79:
#line 470 "parser.y"
                                              {
                                                yylhs.value = new ForStatement((const Identifier *)yystack_[6].value, (Exp*)yystack_[4].value, (Exp*)yystack_[2].value, (Statement*)yystack_[0].value);
                                                ast::copy_pos_between_tokens((ForStatement*)yylhs.value, (ExpKeyword*)yystack_[7].value, (Statement*)yystack_[0].value);
                                              }
#line 2102 "yacc_bison.h"
    break;

  case 80:
#line 475 "parser.y"
{
  yylhs.value = new Read((VariableList*)yystack_[1].value);
  ast::copy_pos_with_check((Read*)yylhs.value, (VariableList*)yystack_[1].value);
}
#line 2111 "yacc_bison.h"
    break;

  case 81:
#line 480 "parser.y"
{
  yylhs.value = new Write((ExpressionList*)yystack_[1].value);
  ast::copy_pos_with_check((Write*)yylhs.value, (ExpressionList*)yystack_[1].value);
}
#line 2120 "yacc_bison.h"
    break;

  case 82:
#line 486 "parser.y"
               {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2128 "yacc_bison.h"
    break;

  case 83:
#line 491 "parser.y"
             {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2136 "yacc_bison.h"
    break;

  case 84:
#line 496 "parser.y"
             {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
   }
#line 2144 "yacc_bison.h"
    break;

  case 85:
#line 501 "parser.y"
                     {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2152 "yacc_bison.h"
    break;

  case 86:
#line 505 "parser.y"
                {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2160 "yacc_bison.h"
    break;

  case 87:
#line 510 "parser.y"
                   {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2168 "yacc_bison.h"
    break;

  case 88:
#line 515 "parser.y"
                     {
   yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
        }
#line 2176 "yacc_bison.h"
    break;

  case 89:
#line 521 "parser.y"
                              {
  yylhs.value = yystack_[2].value ;
  if( ((Node*)yystack_[0].value)->type == Type::Ident ){
    Variable* var = new Variable();
    var->id = ((Ident*)yystack_[0].value)->ident;
    ((Ident*)yystack_[0].value)->ident = nullptr;
    deleteAST((Ident*)yystack_[0].value);
    ast::copy_pos_with_check(var, var->id);
    ((VariableList*)yylhs.value)->params.push_back(var);
    ast::copy_pos_with_check((VariableList*)yylhs.value, var);
  }else{
    ((VariableList*)yylhs.value)->params.push_back((Variable*)yystack_[0].value);
    ast::copy_pos_with_check((VariableList*)yylhs.value, (Variable*)yystack_[0].value);
  }
}
#line 2196 "yacc_bison.h"
    break;

  case 90:
#line 536 "parser.y"
                {
  yylhs.value = new VariableList();
  if( ((Node*)yystack_[0].value)->type == Type::Ident ){
    Variable* var = new Variable();
    var->id = ((Ident*)yystack_[0].value)->ident;
    ((Ident*)yystack_[0].value)->ident = nullptr;
    deleteAST((Ident*)yystack_[0].value);
    ast::copy_pos_with_check(var, var->id);
    ((VariableList*)yylhs.value)->params.push_back(var);
    ast::copy_pos_with_check((VariableList*)yylhs.value, var);
  }else{
    ((VariableList*)yylhs.value)->params.push_back((Variable*)yystack_[0].value);
    ast::copy_pos_with_check((VariableList*)yylhs.value, (Variable*)yystack_[0].value);
  }
}
#line 2216 "yacc_bison.h"
    break;

  case 91:
#line 555 "parser.y"
               {
  if( yystack_[0].value == nullptr ){
    yylhs.value = new Ident((Identifier*)yystack_[1].value);
    }else{
    yylhs.value = new Variable((Identifier*)yystack_[1].value, (ExpressionList*)yystack_[0].value);
    ast::copy_pos_between_tokens((Variable*)yylhs.value, (Identifier*)yystack_[1].value, (ExpressionList*)yystack_[0].value);
  }
}
#line 2229 "yacc_bison.h"
    break;

  case 92:
#line 565 "parser.y"
                      { yylhs.value = nullptr; /* new ExpressionList(); */ }
#line 2235 "yacc_bison.h"
    break;

  case 93:
#line 566 "parser.y"
                                    {
  yylhs.value = yystack_[1].value;
}
#line 2243 "yacc_bison.h"
    break;

  case 94:
#line 571 "parser.y"
                         {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2251 "yacc_bison.h"
    break;

  case 95:
#line 575 "parser.y"
                         {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2259 "yacc_bison.h"
    break;

  case 96:
#line 580 "parser.y"
            {
    yylhs.value = new Ident((const Identifier*)yystack_[0].value);
  //$$ = new ExpCall((const Identifier*)$1, nullptr);
}
#line 2268 "yacc_bison.h"
    break;

  case 97:
#line 584 "parser.y"
                                      {
  yylhs.value = new ExpCall((const Identifier*)yystack_[3].value, (ExpressionList*)yystack_[1].value);
}
#line 2276 "yacc_bison.h"
    break;

  case 98:
#line 587 "parser.y"
                      {
  yylhs.value = new ExpCall((const Identifier*)yystack_[2].value, nullptr);
}
#line 2284 "yacc_bison.h"
    break;

  case 99:
#line 595 "parser.y"
                     {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2292 "yacc_bison.h"
    break;

  case 100:
#line 599 "parser.y"
                     {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2300 "yacc_bison.h"
    break;

  case 101:
#line 603 "parser.y"
         {
  // $$ = new Ident((const Identifier *)($1));
  yylhs.value = yystack_[0].value;
}
#line 2309 "yacc_bison.h"
    break;

  case 102:
#line 609 "parser.y"
                                 {
  yylhs.value = yystack_[2].value;
  ((ExpressionList*)yylhs.value)->explist.push_back((Exp*)yystack_[0].value);
  ast::copy_pos_with_check((ExpressionList*)yylhs.value, (Exp*)yystack_[0].value);
}
#line 2319 "yacc_bison.h"
    break;

  case 103:
#line 614 "parser.y"
                    {
  yylhs.value = new ExpressionList();
  ((ExpressionList*)yylhs.value)->explist.push_back((Exp*)yystack_[0].value);
  ast::copy_pos_with_check((ExpressionList*)yylhs.value, (Exp*)yystack_[0].value);
}
#line 2329 "yacc_bison.h"
    break;

  case 104:
#line 622 "parser.y"
                     {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2337 "yacc_bison.h"
    break;

  case 105:
#line 627 "parser.y"
                                                       {
  yylhs.value = new BiExp((Exp*)yystack_[2].value, (const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);
}
#line 2345 "yacc_bison.h"
    break;

  case 106:
#line 630 "parser.y"
                    { yylhs.value = yystack_[0].value; }
#line 2351 "yacc_bison.h"
    break;

  case 107:
#line 634 "parser.y"
                             { yylhs.value = new BiExp((Exp*)yystack_[2].value, (const Marker*)yystack_[1].value, (Exp*)yystack_[0].value); }
#line 2357 "yacc_bison.h"
    break;

  case 108:
#line 635 "parser.y"
       { yylhs.value = yystack_[0].value; }
#line 2363 "yacc_bison.h"
    break;

  case 109:
#line 638 "parser.y"
                        {
  yylhs.value = new BiExp((Exp*)yystack_[2].value, (const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);
}
#line 2371 "yacc_bison.h"
    break;

  case 110:
#line 641 "parser.y"
         { yylhs.value=yystack_[0].value; }
#line 2377 "yacc_bison.h"
    break;

  case 112:
#line 644 "parser.y"
           {
  yylhs.value = yystack_[0].value;
}
#line 2385 "yacc_bison.h"
    break;

  case 113:
#line 647 "parser.y"
                                   {
  yylhs.value = new ExpCall((const Identifier*)yystack_[3].value, (ExpressionList*)yystack_[1].value);
}
#line 2393 "yacc_bison.h"
    break;

  case 114:
#line 650 "parser.y"
                           {
  yylhs.value = yystack_[1].value;
}
#line 2401 "yacc_bison.h"
    break;

  case 115:
#line 653 "parser.y"
            {
  yylhs.value = new UnExp((const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);
}
#line 2409 "yacc_bison.h"
    break;

  case 116:
#line 656 "parser.y"
               {
  yylhs.value = new UnExp((const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);
}
#line 2417 "yacc_bison.h"
    break;

  case 117:
#line 659 "parser.y"
              {
  yylhs.value = yystack_[0].value;
  }
#line 2425 "yacc_bison.h"
    break;

  case 118:
#line 664 "parser.y"
                     {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2434 "yacc_bison.h"
    break;

  case 119:
#line 669 "parser.y"
                   {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2443 "yacc_bison.h"
    break;

  case 120:
#line 674 "parser.y"
                  {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2452 "yacc_bison.h"
    break;

  case 121:
#line 678 "parser.y"
             {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2461 "yacc_bison.h"
    break;

  case 122:
#line 682 "parser.y"
                {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2470 "yacc_bison.h"
    break;

  case 123:
#line 688 "parser.y"
                  {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2479 "yacc_bison.h"
    break;

  case 124:
#line 692 "parser.y"
             {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2488 "yacc_bison.h"
    break;

  case 125:
#line 696 "parser.y"
             {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2497 "yacc_bison.h"
    break;

  case 126:
#line 700 "parser.y"
                  {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2506 "yacc_bison.h"
    break;

  case 127:
#line 705 "parser.y"
                 {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2515 "yacc_bison.h"
    break;

  case 128:
#line 709 "parser.y"
             {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2524 "yacc_bison.h"
    break;

  case 129:
#line 713 "parser.y"
            {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2533 "yacc_bison.h"
    break;

  case 130:
#line 717 "parser.y"
            {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2542 "yacc_bison.h"
    break;

  case 131:
#line 721 "parser.y"
            {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2551 "yacc_bison.h"
    break;

  case 132:
#line 725 "parser.y"
            {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2560 "yacc_bison.h"
    break;


#line 2564 "yacc_bison.h"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const signed char parser::yypact_ninf_ = -119;

  const signed char parser::yytable_ninf_ = -93;

  const short
  parser::yypact_[] =
  {
      36,    27,  -119,    59,     6,    67,    67,  -119,  -119,    66,
    -119,    31,    31,  -119,    41,    38,    67,  -119,    16,    68,
    -119,  -119,  -119,  -119,  -119,    67,     6,    46,  -119,    25,
    -119,  -119,  -119,    95,    30,     6,    67,  -119,   101,  -119,
    -119,    67,  -119,  -119,  -119,     6,     6,    67,    67,  -119,
     146,  -119,   176,    67,    46,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,    90,    90,  -119,  -119,
      66,    31,    31,  -119,  -119,    31,    31,  -119,     3,  -119,
      67,   182,    64,  -119,     7,     6,  -119,  -119,  -119,  -119,
    -119,  -119,    70,  -119,  -119,  -119,  -119,    30,   101,  -119,
    -119,    14,  -119,  -119,    55,    74,    67,   182,  -119,  -119,
     146,    64,  -119,   111,  -119,  -119,   182,    79,   113,   205,
     167,  -119,   182,   182,  -119,   182,  -119,  -119,   182,   161,
    -119,    73,   222,  -119,   123,    30,   -25,  -119,    67,   190,
      25,  -119,    70,    25,  -119,  -119,   182,    68,   182,  -119,
     146,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
     182,   182,  -119,  -119,  -119,  -119,   182,  -119,  -119,  -119,
      -8,  -119,    25,  -119,   102,    -8,  -119,  -119,   190,    55,
    -119,    30,  -119,  -119,    67,  -119,   182,   114,  -119,    25,
     118,   167,    71,  -119,  -119,  -119,  -119,  -119,    90,   115,
      90,  -119,  -119,   190,  -119,  -119,  -119,   182,  -119,  -119,
     146,  -119,  -119,   190,   102,  -119,   125,  -119,  -119,    90,
    -119,   146,  -119,  -119
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     8,     0,     0,     0,     0,     1,    73,    13,
     101,     5,     0,    14,     0,     0,     0,    99,     0,     0,
       3,     2,    31,    64,    52,     0,     0,     0,   100,     0,
       6,    11,     7,    67,     0,     0,    12,    17,     0,   104,
       4,     0,    56,    57,    69,     0,     0,     0,     0,     9,
      67,    65,     0,    30,     0,    26,    25,    24,    23,    44,
      27,    28,    16,    22,    20,    21,     0,     0,    10,    51,
      13,    58,    58,    86,    82,     0,     0,    76,     0,    72,
       0,   111,     0,    75,    96,     0,    37,    43,    45,    46,
      42,    33,     0,    35,    39,    40,    41,     0,     0,    18,
      19,     0,    53,    54,     0,     0,     0,   111,    70,    68,
      67,     0,   118,   119,   117,   112,   111,    92,     0,   106,
     108,   110,   111,   111,    85,   111,    94,    91,   111,   111,
      34,     0,     0,    15,    67,     0,     0,    61,     0,     0,
       0,    90,    92,     0,   103,    71,   111,     0,   111,    87,
      67,   128,   131,   132,   129,   127,   130,   120,   121,   122,
     111,   111,   123,   124,   125,   126,   111,   115,   116,    74,
       0,    98,     0,    49,     0,     0,    32,    66,     0,     0,
      59,     0,    55,    80,     0,    81,   111,     0,   114,     0,
      78,   107,   105,   109,    95,    93,    97,    50,     0,     0,
       0,    63,    60,     0,    89,   102,    83,   111,   113,    88,
      67,    48,    38,     0,     0,    62,     0,    77,    36,     0,
      84,    67,    47,    79
  };

  const short
  parser::yypgoto_[] =
  {
    -119,  -119,  -119,  -119,   156,  -119,    -6,    88,  -119,  -119,
     109,   -14,  -119,   -59,   -49,  -119,  -119,    81,  -119,    39,
    -119,  -119,  -118,  -119,  -119,  -119,  -119,   -36,  -119,  -119,
    -119,  -119,  -119,   108,  -119,     4,   -87,   -83,  -119,   -23,
    -119,  -119,  -119,   -17,  -106,  -119,  -119,  -119,    91,  -119,
    -119,  -119,  -119,   -48,  -119,   100,    29,  -119,    77,   -13,
      -5,  -102,    53,   -76,    45,    48,   -88,  -119,  -119,  -119,
    -119,  -119
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     3,    21,     4,     5,    14,   135,    15,    16,    26,
      38,   114,    63,    64,    65,    66,    67,    24,    35,    91,
      92,   213,    93,    94,    95,    96,   175,   198,    33,    45,
      46,    47,    48,   103,   136,   137,    25,    52,   102,    77,
      50,   109,    78,     9,    79,    80,   207,   221,   125,    81,
     150,   210,   140,   115,   127,   128,   195,    83,   116,    30,
     117,   143,    41,   144,   119,   120,   121,   122,   123,   160,
     166,   161
  };

  const short
  parser::yytable_[] =
  {
      11,    12,    82,    90,   145,   118,    32,    99,   100,    36,
      49,    27,    29,    31,   132,    22,    40,   138,    53,    34,
      31,   182,   139,   108,    62,    10,   170,   172,    69,    70,
      23,    54,    28,   -29,   167,   168,    68,     1,     8,    22,
     147,     2,    71,    72,   190,    84,   189,    97,    31,   169,
       2,   194,   178,    39,    23,   -29,   -29,   -29,   141,     7,
     201,   110,    82,    17,    10,   126,     8,   -92,   130,     8,
     187,    23,   174,    28,   173,   111,    10,   -29,   193,    56,
      57,    13,    28,    90,   133,   215,    39,    17,    18,    19,
      90,    39,   138,    37,    51,   218,    56,    57,   203,    31,
     -29,   142,    82,    20,   217,    84,    55,    56,    57,    58,
     205,   177,    42,    43,    44,   223,   171,   -28,   -28,   179,
     157,   158,   159,   180,   124,    28,    59,   183,   126,    90,
     185,   216,   181,    31,   188,    17,   204,   126,    51,   211,
     149,   214,    44,   197,   206,    84,   209,   212,   104,   104,
      60,    61,   106,   107,    90,    10,   220,     6,   101,   196,
     222,   129,    82,    98,    90,    44,    55,    56,    57,    58,
      10,   176,    73,    82,    31,    74,   208,    85,   219,   142,
     105,    55,   134,   202,    75,    76,    59,    55,    56,    57,
      58,    10,   131,   184,   148,    55,   186,    86,    87,    88,
      89,    59,   146,   112,   199,    84,   192,    59,   191,     0,
      60,   113,    87,    88,    89,    59,    84,    17,    28,   162,
     163,   164,   165,   186,   112,   186,     0,    55,   200,     0,
       0,    60,   113,     0,     0,     0,     0,     0,    17,     0,
       0,     0,   186,    86,    87,    88,    89,    59,   151,   152,
     153,   154,   155,   156,   157,   158,   159
  };

  const short
  parser::yycheck_[] =
  {
       5,     6,    50,    52,   110,    81,    19,    66,    67,    26,
      33,    16,    18,    18,    97,     1,    29,   104,    35,    25,
      25,   139,   105,    20,    38,     9,   128,   129,    45,    46,
      16,    36,    57,    19,   122,   123,    41,     1,    63,     1,
     116,    14,    47,    48,   150,    50,   148,    53,    53,   125,
      14,    59,   135,    61,    16,    17,    18,    19,   106,     0,
     178,    78,   110,    56,     9,    58,    63,    60,    85,    63,
     146,    16,   131,    57,     1,    80,     9,    63,   166,     6,
       7,    15,    57,   132,    98,   203,    61,    56,    11,    12,
     139,    61,   179,    47,    64,   213,     6,     7,   181,   104,
      62,   106,   150,    62,   210,   110,     5,     6,     7,     8,
     186,   134,    17,    18,    19,   221,   129,     6,     7,   136,
      49,    50,    51,   136,    60,    57,    25,   140,    58,   178,
     143,   207,   138,   138,   147,    56,   184,    58,    64,   198,
      27,   200,    19,    41,    30,   150,    28,    32,    71,    72,
      49,    50,    75,    76,   203,     9,    31,     1,    70,   172,
     219,    84,   210,    54,   213,    19,     5,     6,     7,     8,
       9,   132,    26,   221,   179,    29,   189,     1,   214,   184,
      72,     5,   101,   179,    38,    39,    25,     5,     6,     7,
       8,     9,    92,   140,   117,     5,   143,    21,    22,    23,
      24,    25,   111,    42,   175,   210,   161,    25,   160,    -1,
      49,    50,    22,    23,    24,    25,   221,    56,    57,    52,
      53,    54,    55,   170,    42,   172,    -1,     5,   175,    -1,
      -1,    49,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,   189,    21,    22,    23,    24,    25,    43,    44,
      45,    46,    47,    48,    49,    50,    51
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     1,    14,    66,    68,    69,    69,     0,    63,   108,
       9,   125,   125,    15,    70,    72,    73,    56,   123,   123,
      62,    67,     1,    16,    82,   101,    74,   125,    57,    71,
     124,   125,   124,    93,    71,    83,   108,    47,    75,    61,
     124,   127,    17,    18,    19,    94,    95,    96,    97,   104,
     105,    64,   102,   108,   125,     5,     6,     7,     8,    25,
      49,    50,    76,    77,    78,    79,    80,    81,   125,   108,
     108,   125,   125,    26,    29,    38,    39,   104,   107,   109,
     110,   114,   118,   122,   125,     1,    21,    22,    23,    24,
      79,    84,    85,    87,    88,    89,    90,    71,    75,    78,
      78,    72,   103,    98,   123,    98,   123,   123,    20,   106,
     108,   125,    42,    50,    76,   118,   123,   125,   128,   129,
     130,   131,   132,   133,    60,   113,    58,   119,   120,   123,
     108,   120,   102,    76,    82,    71,    99,   100,   101,   102,
     117,   118,   125,   126,   128,   109,   113,   128,   123,    27,
     115,    43,    44,    45,    46,    47,    48,    49,    50,    51,
     134,   136,    52,    53,    54,    55,   135,   131,   131,   128,
     126,   124,   126,     1,    78,    91,    84,   104,   102,   108,
     124,    71,    87,   124,   127,   124,   127,   128,   124,   126,
     109,   130,   129,   131,    59,   121,   124,    41,    92,   121,
     127,    87,   100,   102,   118,   128,    30,   111,   124,    28,
     116,    78,    32,    86,    78,    87,   128,   109,    87,    92,
      31,   112,    78,   109
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    65,    66,    67,    68,    68,    68,    68,    69,    70,
      71,    71,    72,    72,    73,    74,    74,    75,    76,    76,
      76,    76,    76,    77,    78,    78,    79,    80,    81,    82,
      82,    82,    83,    83,    83,    84,    84,    85,    86,    87,
      87,    87,    87,    88,    79,    89,    90,    91,    91,    91,
      92,    93,    93,    94,    95,    95,    96,    97,    98,    98,
      99,    99,   100,   100,   101,   102,   103,   104,   104,   105,
     106,   107,   107,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     117,   118,   119,   119,   120,   121,   122,   122,   122,   123,
     124,   125,   126,   126,   127,   128,   128,   129,   129,   130,
     130,   131,   131,   131,   131,   131,   131,   131,   132,   133,
     134,   134,   134,   135,   135,   135,   135,   136,   136,   136,
     136,   136,   136
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     4,     1,     5,     2,     4,     5,     1,     4,
       3,     1,     3,     0,     1,     5,     3,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       3,     1,     5,     3,     4,     1,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     3,     1,
       1,     3,     0,     3,     3,     5,     1,     1,     0,     3,
       3,     1,     4,     3,     1,     1,     3,     0,     3,     1,
       1,     3,     1,     1,     3,     1,     1,     6,     4,     8,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     2,     0,     3,     1,     1,     1,     4,     3,     1,
       1,     1,     3,     1,     1,     3,     1,     3,     1,     3,
       1,     0,     1,     4,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "KEYWORD", "STR",
  "CHAR", "REAL", "INT", "BOOL", "IDENT", "NULLPTR", "ERRORTOKEN",
  "COMMENT", "LENGTH", "KEYWORD_PROGRAM", "KEYWORD_CONST", "KEYWORD_VAR",
  "KEYWORD_PROCEDURE", "KEYWORD_FUNCTION", "KEYWORD_BEGIN", "KEYWORD_END",
  "KEYWORD_ARRAY", "KEYWORD_INTEGER", "KEYWORD_REAL", "KEYWORD_BOOLEAN",
  "KEYWORD_CHAR", "KEYWORD_IF", "KEYWORD_THEN", "KEYWORD_ELSE",
  "KEYWORD_FOR", "KEYWORD_TO", "KEYWORD_DO", "KEYWORD_OF", "KEYWORD_DIV",
  "KEYWORD_MOD", "KEYWORD_AND", "KEYWORD_OR", "KEYWORD_NOT",
  "KEYWORD_READ", "KEYWORD_WRITE", "KEYWORD_LENGTH", "MARKER_RANGE",
  "MARKER_LOGICNOT", "MARKER_NEQ", "MARKER_LE", "MARKER_GE", "MARKER_LT",
  "MARKER_EQ", "MARKER_GT", "MARKER_ADD", "MARKER_SUB", "MARKER_LOGICOR",
  "MARKER_MUL", "MARKER_DIV", "MARKER_MOD", "MARKER_LOGICAND",
  "MARKER_LPAREN", "MARKER_RPAREN", "MARKER_LBRACKET", "MARKER_RBRACKET",
  "MARKER_ASSIGN", "MARKER_COMMA", "MARKER_DOT", "MARKER_SEMICOLON",
  "MARKER_COLON", "$accept", "programstruct", "dot", "program_head",
  "program", "program_body", "idlist", "const_declarations", "const",
  "const_declaration", "eq", "const_value", "bool", "num", "char", "add",
  "sub", "var_declarations", "var_declaration", "type", "array", "of",
  "basic_type", "integer", "real", "boolean", "period", "range",
  "subprogram_declarations", "subprogram", "subprogram_head", "procedure",
  "function", "formal_parameter", "parameter_list", "parameter", "var",
  "colon", "subprogram_body", "compound_statement", "begin", "end",
  "statement_list", "semicolon", "statement", "for", "to", "do", "assign",
  "if", "then", "else", "variable_list", "variable", "id_varpart",
  "lbracket", "rbracket", "procedure_call", "lparen", "rparen", "id",
  "expression_list", "comma", "expression", "simple_expression", "term",
  "factor", "not", "unimus", "addop", "mulop", "relop", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    84,    84,    93,    99,   102,   105,   111,   126,   131,
     137,   142,   151,   154,   159,   165,   170,   177,   183,   184,
     185,   186,   187,   190,   192,   195,   200,   205,   210,   215,
     216,   219,   227,   233,   241,   252,   255,   262,   267,   273,
     274,   275,   276,   279,   284,   289,   294,   300,   304,   308,
     319,   324,   332,   337,   344,   347,   352,   358,   364,   365,
     374,   379,   389,   392,   398,   404,   409,   414,   415,   423,
     428,   434,   441,   451,   456,   457,   458,   459,   464,   469,
     474,   479,   486,   491,   496,   501,   505,   510,   515,   521,
     536,   555,   565,   566,   571,   575,   580,   584,   587,   595,
     599,   603,   609,   614,   622,   627,   630,   634,   635,   638,
     641,   643,   644,   647,   650,   653,   656,   659,   664,   669,
     674,   678,   682,   688,   692,   696,   700,   705,   709,   713,
     717,   721,   725
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::symbol_kind_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     3,     4,     5,     6,     7,     8,     9,     2,    10,
      11,    12,    13,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    41,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      44,    45,    46,    47,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    49,    50,    51,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,    53,    54,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    56,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    58,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    60,    61,
      62,    63,    64,     1,     2
    };
    const int user_token_number_max_ = 614;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= user_token_number_max_)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 3131 "yacc_bison.h"

#line 729 "parser.y"

