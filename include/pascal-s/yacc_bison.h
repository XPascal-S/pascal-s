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
# define YYDEBUG 1
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
  const Token* current_token;
  virtual int yylex(void**) = 0;
    virtual void access_ast(void*) = 0;
 virtual void add_error(PascalSError*) = 0;
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

      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

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

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);



    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const { return yyla_; }
      symbol_kind_type token () const { return yyla_.kind (); }
      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif

    /// Check the lookahead yytoken.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_check_ (symbol_kind_type yytoken) const;
    /// Establish the initial context if no initial context currently exists.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_establish_ (symbol_kind_type yytoken);
    /// Discard any previous initial lookahead context because of event.
    /// \param event  the event which caused the lookahead to be discarded.
    ///               Only used for debbuging output.
    void yy_lac_discard_ (const char* event);

    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
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

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);



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
    /// The stack for LAC.
    /// Logically, the yy_lac_stack's lifetime is confined to the function
    /// yy_lac_check_. We just store it as a member of this class to hold
    /// on to the memory and to avoid frequent reallocations.
    /// Since yy_lac_check_ is const, this member must be mutable.
    mutable std::vector<state_type> yylac_stack_;
    /// Whether an initial LAC context was established.
    bool yy_lac_established_;


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
      yylast_ = 253,     ///< Last index in yytable_.
      yynnts_ = 72,  ///< Number of nonterminal symbols.
      yyfinal_ = 7 ///< Termination state number.
    };



  };


} // yy
#line 955 "yacc_bison.h"









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
#line 1035 "yacc_bison.h"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false)
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

    /// Discard the LAC context in case there still is one left from a
    /// previous invocation.
    yy_lac_discard_ ("init");

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
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
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
#line 88 "parser.y"
                                                        {
  yylhs.value = new ast::Program((ProgramHead*)yystack_[3].value, (ProgramBody*)yystack_[1].value);
  access_ast(yylhs.value);
  //printf("finish!\n");
 }
#line 1500 "yacc_bison.h"
    break;

  case 3:
#line 93 "parser.y"
        {
  // printf("keep error");
  YYABORT;
  }
#line 1509 "yacc_bison.h"
    break;

  case 4:
#line 101 "parser.y"
               {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
 }
#line 1517 "yacc_bison.h"
    break;

  case 5:
#line 107 "parser.y"
                                {
  yylhs.value = new ProgramHead((const ExpKeyword*)yystack_[4].value, new Ident((const Identifier*)yystack_[3].value), (IdentList*)yystack_[1].value);
}
#line 1525 "yacc_bison.h"
    break;

  case 6:
#line 110 "parser.y"
            {
  yylhs.value = new ProgramHead((const ExpKeyword*)yystack_[1].value, new Ident((const Identifier*)yystack_[0].value));
}
#line 1533 "yacc_bison.h"
    break;

  case 7:
#line 113 "parser.y"
                          {
  IdentList* idlist = new IdentList();
  ast::copy_pos_with_check(idlist, (ExpMarker*)yystack_[1].value);
  ast::copy_pos_with_check(idlist, (ExpMarker*)yystack_[0].value);
  yylhs.value = new ProgramHead((const ExpKeyword*)yystack_[3].value, new Ident((const Identifier*)yystack_[2].value), idlist);
}
#line 1544 "yacc_bison.h"
    break;

  case 8:
#line 119 "parser.y"
                                {
  char* errinfo = "Program Head failed at";
  PascalSParseError* err = new PascalSParseError(__FUNCTION__, errinfo, PascalSErrno::ParseError);
  if( yystack_[5].value != nullptr ){
    err->line = ((Node*)yystack_[5].value)->line;
    err->column = ((Node*)yystack_[5].value)->column + ((Node*)yystack_[5].value)->length;
    err->offset = ((Node*)yystack_[5].value)->offset + ((Node*)yystack_[5].value)->length;
  }
  add_error(err);
  yyerrok;
}
#line 1560 "yacc_bison.h"
    break;

  case 9:
#line 135 "parser.y"
                        {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 1568 "yacc_bison.h"
    break;

  case 10:
#line 140 "parser.y"
                                                                                             {
  yylhs.value = new ProgramBody((ConstDecls*)yystack_[3].value, (VarDecls*)yystack_[2].value, (SubprogramDecls*)yystack_[1].value, (CompoundStatement*)yystack_[0].value);
}
#line 1576 "yacc_bison.h"
    break;

  case 11:
#line 146 "parser.y"
                 {
  yylhs.value = yystack_[2].value;
  ((IdentList*)yylhs.value)->idents.push_back((Identifier*)yystack_[0].value);
  ast::copy_pos_with_check((IdentList*)yylhs.value, (Identifier*)yystack_[0].value);
}
#line 1586 "yacc_bison.h"
    break;

  case 12:
#line 151 "parser.y"
          {
  yylhs.value = new IdentList();
  ((IdentList*)yylhs.value)->idents.push_back((Identifier*)yystack_[0].value);
  ast::copy_pos_with_check((IdentList*)yylhs.value, (Identifier*)yystack_[0].value);
}
#line 1596 "yacc_bison.h"
    break;

  case 13:
#line 160 "parser.y"
                                  {
  yylhs.value = yystack_[1].value;
}
#line 1604 "yacc_bison.h"
    break;

  case 14:
#line 163 "parser.y"
                                        { yylhs.value = nullptr; }
#line 1610 "yacc_bison.h"
    break;

  case 15:
#line 168 "parser.y"
                   {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 1618 "yacc_bison.h"
    break;

  case 16:
#line 174 "parser.y"
                                              {
  yylhs.value = yystack_[4].value;
  ConstDecl* constDecl = new ConstDecl((const Identifier*)yystack_[2].value, (Exp*)yystack_[0].value);
  ((ConstDecls*)yylhs.value)->decls.push_back(constDecl);
}
#line 1628 "yacc_bison.h"
    break;

  case 17:
#line 179 "parser.y"
                    {
  ConstDecl* constDecl = new ConstDecl((const Identifier*)yystack_[2].value, (Exp*)yystack_[0].value);
  yylhs.value = new ConstDecls();
  ((ConstDecls*)yylhs.value)->decls.push_back(constDecl);
}
#line 1638 "yacc_bison.h"
    break;

  case 18:
#line 186 "parser.y"
             {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 1646 "yacc_bison.h"
    break;

  case 19:
#line 192 "parser.y"
          {yylhs.value = new UnExp((const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);}
#line 1652 "yacc_bison.h"
    break;

  case 20:
#line 193 "parser.y"
          {yylhs.value = new UnExp((const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);}
#line 1658 "yacc_bison.h"
    break;

  case 21:
#line 194 "parser.y"
          {yylhs.value = yystack_[0].value;}
#line 1664 "yacc_bison.h"
    break;

  case 22:
#line 195 "parser.y"
          {yylhs.value = yystack_[0].value;}
#line 1670 "yacc_bison.h"
    break;

  case 23:
#line 196 "parser.y"
          {yylhs.value = yystack_[0].value;}
#line 1676 "yacc_bison.h"
    break;

  case 24:
#line 199 "parser.y"
         {yylhs.value = new ExpConstantBoolean(((const ConstantBoolean*)(yystack_[0].value)));}
#line 1682 "yacc_bison.h"
    break;

  case 25:
#line 201 "parser.y"
        {
  yylhs.value = new ExpConstantInteger(((const ConstantInteger*)(yystack_[0].value)));
}
#line 1690 "yacc_bison.h"
    break;

  case 26:
#line 204 "parser.y"
       {
  yylhs.value = new ExpConstantReal(((const ConstantReal*)(yystack_[0].value)));
  }
#line 1698 "yacc_bison.h"
    break;

  case 27:
#line 209 "parser.y"
          {
  yylhs.value = new ExpConstantChar(((const ConstantChar*)(yystack_[0].value)));
}
#line 1706 "yacc_bison.h"
    break;

  case 28:
#line 214 "parser.y"
               {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 1714 "yacc_bison.h"
    break;

  case 29:
#line 219 "parser.y"
               {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 1722 "yacc_bison.h"
    break;

  case 30:
#line 224 "parser.y"
                               { yylhs.value = nullptr;  /* new ExpVoid(); */ }
#line 1728 "yacc_bison.h"
    break;

  case 31:
#line 225 "parser.y"
                               {
  yylhs.value = yystack_[1].value;
}
#line 1736 "yacc_bison.h"
    break;

  case 32:
#line 228 "parser.y"
        {
  yylhs.value = yystack_[1].value;
  ast::printAST((Node*)yystack_[1].value);
  char* errinfo = "Var Declarations failed at";
  PascalSParseError* err = new PascalSParseError(__FUNCTION__, errinfo, PascalSErrno::ParseError);
  if( yystack_[1].value != nullptr ){
    err->line = ((Node*)yystack_[1].value)->line;
    err->column = ((Node*)yystack_[1].value)->column + ((Node*)yystack_[1].value)->length;
    err->offset = ((Node*)yystack_[1].value)->offset + ((Node*)yystack_[1].value)->length;
  }
  add_error(err);
  yyerrok;
}
#line 1754 "yacc_bison.h"
    break;

  case 33:
#line 245 "parser.y"
                                              {
  yylhs.value = yystack_[4].value;
  VarDecl* vdecl = new VarDecl((IdentList*)yystack_[2].value, (TypeSpec*)yystack_[0].value);
  ((VarDecls*)yylhs.value)->decls.push_back(vdecl);
  ast::copy_pos_with_check((VarDecls*)yylhs.value, vdecl);
}
#line 1765 "yacc_bison.h"
    break;

  case 34:
#line 251 "parser.y"
                    {
  yylhs.value = new VarDecls();
  VarDecl* vdecl = new VarDecl((IdentList*)yystack_[2].value, (TypeSpec*)yystack_[0].value);
  ast::copy_pos_with_check((VarDecls*)yylhs.value, (IdentList*)yystack_[2].value);
  ((VarDecls*)yylhs.value)->decls.push_back(vdecl);
  ast::copy_pos_with_check((VarDecls*)yylhs.value, vdecl);
}
#line 1777 "yacc_bison.h"
    break;

  case 35:
#line 258 "parser.y"
                               {
  yylhs.value = new VarDecls();
  ast::copy_pos_between_tokens((VarDecls*)yylhs.value, (IdentList*)yystack_[3].value, (Token*)yystack_[0].value);
  char* errinfo = "Var Declaration failed at";
  PascalSParseError* err = new PascalSParseError(__FUNCTION__, errinfo, PascalSErrno::ParseError);
  if( yystack_[4].value != nullptr ){
    err->line = ((Node*)yystack_[4].value)->line;
    err->column = ((Node*)yystack_[4].value)->column + ((Node*)yystack_[4].value)->length;
    err->offset = ((Node*)yystack_[4].value)->offset + ((Node*)yystack_[4].value)->length;
  }
  add_error(err);
  // yyerrok;
}
#line 1795 "yacc_bison.h"
    break;

  case 36:
#line 274 "parser.y"
                     {
  yylhs.value = yystack_[0].value;
}
#line 1803 "yacc_bison.h"
    break;

  case 37:
#line 277 "parser.y"
                                                       {
  yylhs.value = yystack_[3].value;
  ((ArrayTypeSpec*)yylhs.value)->keyword = ((BasicTypeSpec*)yystack_[0].value)->keyword;
  ast::copy_pos_with_check((ArrayTypeSpec*)yylhs.value, ((BasicTypeSpec*)yystack_[0].value)->keyword);
}
#line 1813 "yacc_bison.h"
    break;

  case 38:
#line 282 "parser.y"
                                             {
  yylhs.value = new ArrayTypeSpec(nullptr);
  ((ArrayTypeSpec*)yylhs.value)->keyword = ((BasicTypeSpec*)yystack_[0].value)->keyword;
  // ast::copy_pos_with_check((ArrayTypeSpec*)$$, ((BasicTypeSpec*)$5)->keyword);
  ast::copy_pos_between_tokens((ArrayTypeSpec*)yylhs.value, (const Keyword*)yystack_[4].value, (BasicTypeSpec*)yystack_[0].value);
  yyerrok;
}
#line 1825 "yacc_bison.h"
    break;

  case 39:
#line 291 "parser.y"
                    {
  // $$ = new ExpKeyword((const Keyword *)($1));
  yylhs.value = yystack_[0].value;
}
#line 1834 "yacc_bison.h"
    break;

  case 40:
#line 297 "parser.y"
              {
  // $$ = new ExpKeyword((const Keyword *)($1));
  yylhs.value = yystack_[0].value;
}
#line 1843 "yacc_bison.h"
    break;

  case 41:
#line 304 "parser.y"
                  {yylhs.value = yystack_[0].value;}
#line 1849 "yacc_bison.h"
    break;

  case 42:
#line 305 "parser.y"
                {yylhs.value = yystack_[0].value;}
#line 1855 "yacc_bison.h"
    break;

  case 43:
#line 306 "parser.y"
                   {yylhs.value = yystack_[0].value;}
#line 1861 "yacc_bison.h"
    break;

  case 44:
#line 307 "parser.y"
                {yylhs.value = yystack_[0].value;}
#line 1867 "yacc_bison.h"
    break;

  case 45:
#line 310 "parser.y"
                       {
  yylhs.value = new BasicTypeSpec((const Keyword *)(yystack_[0].value));
}
#line 1875 "yacc_bison.h"
    break;

  case 46:
#line 315 "parser.y"
                 {
  yylhs.value = new BasicTypeSpec((const Keyword *)(yystack_[0].value));
}
#line 1883 "yacc_bison.h"
    break;

  case 47:
#line 320 "parser.y"
                 {
  yylhs.value = new BasicTypeSpec((const Keyword *)(yystack_[0].value));
}
#line 1891 "yacc_bison.h"
    break;

  case 48:
#line 325 "parser.y"
                       {
  yylhs.value = new BasicTypeSpec((const Keyword *)(yystack_[0].value));
}
#line 1899 "yacc_bison.h"
    break;

  case 49:
#line 331 "parser.y"
                                  {
  yylhs.value = yystack_[4].value;
  ((ArrayTypeSpec*)yylhs.value)->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)yystack_[2].value)->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)yystack_[0].value)->value)->attr)));
}
#line 1908 "yacc_bison.h"
    break;

  case 50:
#line 335 "parser.y"
                                   {
  yylhs.value = new ArrayTypeSpec(nullptr);
  ((ArrayTypeSpec*)yylhs.value)->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)yystack_[2].value)->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)yystack_[0].value)->value)->attr)));
}
#line 1917 "yacc_bison.h"
    break;

  case 51:
#line 339 "parser.y"
                           {
    char* errinfo = "Expect NUM";
    PascalSParseError* err = new PascalSParseError(__FUNCTION__, errinfo, PascalSErrno::ParseError);
    err->line = ((Node*)yystack_[2].value)->line;
    err->column = ((Node*)yystack_[2].value)->column + ((Node*)yystack_[2].value)->length;
    err->offset = ((Node*)yystack_[2].value)->offset + ((Node*)yystack_[2].value)->length;
    add_error(err);
    yyerrok;
}
#line 1931 "yacc_bison.h"
    break;

  case 52:
#line 349 "parser.y"
                   {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 1939 "yacc_bison.h"
    break;

  case 53:
#line 354 "parser.y"
                                              {
  if( yystack_[2].value == nullptr ){
    yylhs.value = new SubprogramDecls();
  }else{
    yylhs.value = yystack_[2].value;
  }
  ((SubprogramDecls*)yylhs.value)->subprogram.push_back(((Subprogram*)yystack_[1].value));
}
#line 1952 "yacc_bison.h"
    break;

  case 54:
#line 362 "parser.y"
  { yylhs.value = nullptr;  }
#line 1958 "yacc_bison.h"
    break;

  case 55:
#line 367 "parser.y"
                                          {
  yylhs.value = new Subprogram((SubprogramHead*)yystack_[2].value, (SubprogramBody*)yystack_[0].value);
}
#line 1966 "yacc_bison.h"
    break;

  case 56:
#line 374 "parser.y"
                                {
  yylhs.value = new SubprogramHead((const Keyword*)yystack_[2].value, (const Identifier*)yystack_[1].value, (ParamList*)yystack_[0].value, nullptr);
}
#line 1974 "yacc_bison.h"
    break;

  case 57:
#line 377 "parser.y"
                                                 {
  yylhs.value = new SubprogramHead((const Keyword*)yystack_[4].value, (const Identifier*)yystack_[3].value, (ParamList*)yystack_[2].value, (BasicTypeSpec*)yystack_[0].value);
}
#line 1982 "yacc_bison.h"
    break;

  case 58:
#line 382 "parser.y"
                            {
  // $$ = new ExpKeyword((const Keyword *)($1));
  yylhs.value = yystack_[0].value;
}
#line 1991 "yacc_bison.h"
    break;

  case 59:
#line 388 "parser.y"
                         {
  //$$ = new ExpKeyword((const Keyword *)($1));
  yylhs.value = yystack_[0].value;
}
#line 2000 "yacc_bison.h"
    break;

  case 60:
#line 394 "parser.y"
                  { yylhs.value =  nullptr; /* new ParamList(); */  }
#line 2006 "yacc_bison.h"
    break;

  case 61:
#line 395 "parser.y"
                               {
  yylhs.value = yystack_[1].value;
}
#line 2014 "yacc_bison.h"
    break;

  case 62:
#line 404 "parser.y"
                                     {
  yylhs.value = yystack_[2].value;
  ((ParamList*)yylhs.value)->params.push_back((ParamSpec*)yystack_[0].value);
  ast::copy_pos_with_check((ParamList*)yylhs.value, (ParamSpec*)yystack_[0].value);
}
#line 2024 "yacc_bison.h"
    break;

  case 63:
#line 409 "parser.y"
                                {
  yylhs.value = new ParamList();
  ((ParamList*)yylhs.value)->params.push_back((ParamSpec*)yystack_[0].value);
  ast::copy_pos_with_check((ParamList*)yylhs.value, (ParamSpec*)yystack_[0].value);
  }
#line 2034 "yacc_bison.h"
    break;

  case 64:
#line 419 "parser.y"
                                    {
  yylhs.value = new ParamSpec((const Keyword*)yystack_[3].value, (IdentList*)yystack_[2].value, (TypeSpec*)yystack_[0].value);
}
#line 2042 "yacc_bison.h"
    break;

  case 65:
#line 422 "parser.y"
                                {
  yylhs.value = new ParamSpec(nullptr, (IdentList*)yystack_[2].value, (TypeSpec*)yystack_[0].value);
}
#line 2050 "yacc_bison.h"
    break;

  case 66:
#line 428 "parser.y"
               {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2058 "yacc_bison.h"
    break;

  case 67:
#line 434 "parser.y"
                   {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2066 "yacc_bison.h"
    break;

  case 68:
#line 439 "parser.y"
                                                        {
  yylhs.value = new SubprogramBody((ConstDecls*)yystack_[2].value, (VarDecls*)yystack_[1].value, (CompoundStatement*)yystack_[0].value);
}
#line 2074 "yacc_bison.h"
    break;

  case 69:
#line 444 "parser.y"
                                { yylhs.value = nullptr; }
#line 2080 "yacc_bison.h"
    break;

  case 70:
#line 445 "parser.y"
                                   {
  yylhs.value = new CompoundStatement((StatementList*)yystack_[1].value);
}
#line 2088 "yacc_bison.h"
    break;

  case 71:
#line 453 "parser.y"
                   {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2096 "yacc_bison.h"
    break;

  case 72:
#line 458 "parser.y"
               {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
             }
#line 2104 "yacc_bison.h"
    break;

  case 73:
#line 464 "parser.y"
                                       {
  yylhs.value = yystack_[2].value;
  if( yystack_[0].value != nullptr ){
    ((StatementList*)yylhs.value)->statement.push_back((Statement*)yystack_[0].value);
    ast::copy_pos_with_check((StatementList*)yylhs.value, (Statement*)yystack_[0].value);
  }
}
#line 2116 "yacc_bison.h"
    break;

  case 74:
#line 471 "parser.y"
            {
  yylhs.value = new StatementList();
  if( yystack_[0].value != nullptr ){
    ((StatementList*)yylhs.value)->statement.push_back((Statement*)yystack_[0].value);
    ast::copy_pos_with_check((StatementList*)yylhs.value, (Statement*)yystack_[0].value);
  }
}
#line 2128 "yacc_bison.h"
    break;

  case 75:
#line 481 "parser.y"
                           {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2136 "yacc_bison.h"
    break;

  case 76:
#line 486 "parser.y"
                                                      {yylhs.value = new ExecStatement(new ExpAssign((Variable*)yystack_[2].value, (Exp*)yystack_[0].value));}
#line 2142 "yacc_bison.h"
    break;

  case 77:
#line 487 "parser.y"
                                                      {yylhs.value = new ExecStatement((Exp*)yystack_[0].value);}
#line 2148 "yacc_bison.h"
    break;

  case 78:
#line 488 "parser.y"
                                                      {yylhs.value = yystack_[0].value;}
#line 2154 "yacc_bison.h"
    break;

  case 79:
#line 490 "parser.y"
                                      {
                                        yylhs.value = new IfElseStatement((Exp*)yystack_[4].value, (Statement*)yystack_[2].value, (Statement*)yystack_[0].value);
                                        ast::copy_pos_between_tokens((IfElseStatement*)yylhs.value, (ExpKeyword*)yystack_[5].value, (Statement*)yystack_[0].value);
                                      }
#line 2163 "yacc_bison.h"
    break;

  case 80:
#line 495 "parser.y"
{
  yylhs.value = new IfElseStatement((Exp*)yystack_[2].value, (Statement*)yystack_[0].value, nullptr);
  ast::copy_pos_between_tokens((IfElseStatement*)yylhs.value, (ExpKeyword*)yystack_[3].value, (Statement*)yystack_[0].value);
}
#line 2172 "yacc_bison.h"
    break;

  case 81:
#line 500 "parser.y"
                                              {
                                                yylhs.value = new ForStatement((const Identifier *)yystack_[6].value, (Exp*)yystack_[4].value, (Exp*)yystack_[2].value, (Statement*)yystack_[0].value);
                                                ast::copy_pos_between_tokens((ForStatement*)yylhs.value, (ExpKeyword*)yystack_[7].value, (Statement*)yystack_[0].value);
                                              }
#line 2181 "yacc_bison.h"
    break;

  case 82:
#line 505 "parser.y"
{
  yylhs.value = new Read((VariableList*)yystack_[1].value);
  ast::copy_pos_with_check((Read*)yylhs.value, (VariableList*)yystack_[1].value);
}
#line 2190 "yacc_bison.h"
    break;

  case 83:
#line 510 "parser.y"
{
  yylhs.value = new Write((ExpressionList*)yystack_[1].value);
  ast::copy_pos_with_check((Write*)yylhs.value, (ExpressionList*)yystack_[1].value);
}
#line 2199 "yacc_bison.h"
    break;

  case 84:
#line 516 "parser.y"
               {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2207 "yacc_bison.h"
    break;

  case 85:
#line 521 "parser.y"
             {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2215 "yacc_bison.h"
    break;

  case 86:
#line 526 "parser.y"
             {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
   }
#line 2223 "yacc_bison.h"
    break;

  case 87:
#line 531 "parser.y"
                     {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2231 "yacc_bison.h"
    break;

  case 88:
#line 535 "parser.y"
                {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2239 "yacc_bison.h"
    break;

  case 89:
#line 540 "parser.y"
                   {
  yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
}
#line 2247 "yacc_bison.h"
    break;

  case 90:
#line 545 "parser.y"
                     {
   yylhs.value = new ExpKeyword((const Keyword *)(yystack_[0].value));
        }
#line 2255 "yacc_bison.h"
    break;

  case 91:
#line 551 "parser.y"
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
#line 2275 "yacc_bison.h"
    break;

  case 92:
#line 566 "parser.y"
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
#line 2295 "yacc_bison.h"
    break;

  case 93:
#line 585 "parser.y"
               {
  if( yystack_[0].value == nullptr ){
    yylhs.value = new Ident((Identifier*)yystack_[1].value);
    }else{
    yylhs.value = new Variable((Identifier*)yystack_[1].value, (ExpressionList*)yystack_[0].value);
    ast::copy_pos_between_tokens((Variable*)yylhs.value, (Identifier*)yystack_[1].value, (ExpressionList*)yystack_[0].value);
  }
}
#line 2308 "yacc_bison.h"
    break;

  case 94:
#line 595 "parser.y"
                      { yylhs.value = nullptr; /* new ExpressionList(); */ }
#line 2314 "yacc_bison.h"
    break;

  case 95:
#line 596 "parser.y"
                                    {
  yylhs.value = yystack_[1].value;
}
#line 2322 "yacc_bison.h"
    break;

  case 96:
#line 601 "parser.y"
                         {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2330 "yacc_bison.h"
    break;

  case 97:
#line 605 "parser.y"
                         {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2338 "yacc_bison.h"
    break;

  case 98:
#line 610 "parser.y"
            {
    yylhs.value = new Ident((const Identifier*)yystack_[0].value);
  //$$ = new ExpCall((const Identifier*)$1, nullptr);
}
#line 2347 "yacc_bison.h"
    break;

  case 99:
#line 614 "parser.y"
                                      {
  yylhs.value = new ExpCall((const Identifier*)yystack_[3].value, (ExpressionList*)yystack_[1].value);
}
#line 2355 "yacc_bison.h"
    break;

  case 100:
#line 617 "parser.y"
                      {
  yylhs.value = new ExpCall((const Identifier*)yystack_[2].value, nullptr);
}
#line 2363 "yacc_bison.h"
    break;

  case 101:
#line 625 "parser.y"
                     {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2371 "yacc_bison.h"
    break;

  case 102:
#line 629 "parser.y"
                     {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2379 "yacc_bison.h"
    break;

  case 103:
#line 633 "parser.y"
         {
  // $$ = new Ident((const Identifier *)($1));
  yylhs.value = yystack_[0].value;
}
#line 2388 "yacc_bison.h"
    break;

  case 104:
#line 639 "parser.y"
                                 {
  yylhs.value = yystack_[2].value;
  ((ExpressionList*)yylhs.value)->explist.push_back((Exp*)yystack_[0].value);
  ast::copy_pos_with_check((ExpressionList*)yylhs.value, (Exp*)yystack_[0].value);
}
#line 2398 "yacc_bison.h"
    break;

  case 105:
#line 644 "parser.y"
                    {
  yylhs.value = new ExpressionList();
  ((ExpressionList*)yylhs.value)->explist.push_back((Exp*)yystack_[0].value);
  ast::copy_pos_with_check((ExpressionList*)yylhs.value, (Exp*)yystack_[0].value);
}
#line 2408 "yacc_bison.h"
    break;

  case 106:
#line 652 "parser.y"
                     {
  yylhs.value = new ExpMarker((const Marker *)(yystack_[0].value));
}
#line 2416 "yacc_bison.h"
    break;

  case 107:
#line 657 "parser.y"
                                                       {
  yylhs.value = new BiExp((Exp*)yystack_[2].value, (const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);
}
#line 2424 "yacc_bison.h"
    break;

  case 108:
#line 660 "parser.y"
                    { yylhs.value = yystack_[0].value; }
#line 2430 "yacc_bison.h"
    break;

  case 109:
#line 664 "parser.y"
                             { yylhs.value = new BiExp((Exp*)yystack_[2].value, (const Marker*)yystack_[1].value, (Exp*)yystack_[0].value); }
#line 2436 "yacc_bison.h"
    break;

  case 110:
#line 665 "parser.y"
       { yylhs.value = yystack_[0].value; }
#line 2442 "yacc_bison.h"
    break;

  case 111:
#line 668 "parser.y"
                        {
  yylhs.value = new BiExp((Exp*)yystack_[2].value, (const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);
}
#line 2450 "yacc_bison.h"
    break;

  case 112:
#line 671 "parser.y"
         { yylhs.value=yystack_[0].value; }
#line 2456 "yacc_bison.h"
    break;

  case 114:
#line 674 "parser.y"
           {
  yylhs.value = yystack_[0].value;
}
#line 2464 "yacc_bison.h"
    break;

  case 115:
#line 677 "parser.y"
                                   {
  yylhs.value = new ExpCall((const Identifier*)yystack_[3].value, (ExpressionList*)yystack_[1].value);
}
#line 2472 "yacc_bison.h"
    break;

  case 116:
#line 680 "parser.y"
                           {
  yylhs.value = yystack_[1].value;
}
#line 2480 "yacc_bison.h"
    break;

  case 117:
#line 683 "parser.y"
            {
  yylhs.value = new UnExp((const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);
}
#line 2488 "yacc_bison.h"
    break;

  case 118:
#line 686 "parser.y"
               {
  yylhs.value = new UnExp((const Marker*)yystack_[1].value, (Exp*)yystack_[0].value);
}
#line 2496 "yacc_bison.h"
    break;

  case 119:
#line 689 "parser.y"
              {
  yylhs.value = yystack_[0].value;
  }
#line 2504 "yacc_bison.h"
    break;

  case 120:
#line 694 "parser.y"
                     {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2513 "yacc_bison.h"
    break;

  case 121:
#line 699 "parser.y"
                   {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2522 "yacc_bison.h"
    break;

  case 122:
#line 704 "parser.y"
                  {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2531 "yacc_bison.h"
    break;

  case 123:
#line 708 "parser.y"
             {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2540 "yacc_bison.h"
    break;

  case 124:
#line 712 "parser.y"
                {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2549 "yacc_bison.h"
    break;

  case 125:
#line 718 "parser.y"
                  {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2558 "yacc_bison.h"
    break;

  case 126:
#line 722 "parser.y"
             {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2567 "yacc_bison.h"
    break;

  case 127:
#line 726 "parser.y"
             {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2576 "yacc_bison.h"
    break;

  case 128:
#line 730 "parser.y"
                  {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2585 "yacc_bison.h"
    break;

  case 129:
#line 735 "parser.y"
                 {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
}
#line 2594 "yacc_bison.h"
    break;

  case 130:
#line 739 "parser.y"
             {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2603 "yacc_bison.h"
    break;

  case 131:
#line 743 "parser.y"
            {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2612 "yacc_bison.h"
    break;

  case 132:
#line 747 "parser.y"
            {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2621 "yacc_bison.h"
    break;

  case 133:
#line 751 "parser.y"
            {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2630 "yacc_bison.h"
    break;

  case 134:
#line 755 "parser.y"
            {
  // $$ = new ExpMarker((const Marker *)($1));
  yylhs.value = yystack_[0].value ;
  }
#line 2639 "yacc_bison.h"
    break;


#line 2643 "yacc_bison.h"

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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
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
      yy_lac_discard_ ("error recovery");
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

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "KEYWORD", "STR", "CHAR",
  "REAL", "INT", "BOOL", "IDENT", "NULLPTR", "ERRORTOKEN", "COMMENT",
  "LENGTH", "KEYWORD_PROGRAM", "KEYWORD_CONST", "KEYWORD_VAR",
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
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if YYDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }


  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if YYDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (!yy_lac_established_)
      {
#if YYDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
    return true;
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* evt)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << evt << '\n';
        yy_lac_established_ = false;
      }
  }

  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short parser::yypact_ninf_ = -161;

  const signed char parser::yytable_ninf_ = -95;

  const short
  parser::yypact_[] =
  {
      25,    23,  -161,    73,   -23,    79,    79,  -161,  -161,    81,
    -161,    44,    44,  -161,    69,    62,    79,  -161,    14,    50,
    -161,  -161,  -161,  -161,  -161,    79,   -23,    70,  -161,     9,
    -161,  -161,  -161,   102,   -29,   -23,    79,  -161,   183,  -161,
    -161,    79,  -161,  -161,  -161,   -23,   -23,    79,    79,  -161,
     177,  -161,   213,    79,    70,  -161,  -161,  -161,  -161,  -161,
    -161,  -161,  -161,  -161,  -161,  -161,    45,    45,  -161,  -161,
      81,    44,    44,  -161,  -161,    44,    44,  -161,     1,  -161,
      79,   175,    75,  -161,    55,   -23,  -161,  -161,  -161,  -161,
    -161,  -161,    86,  -161,  -161,  -161,  -161,   -29,   183,  -161,
    -161,    40,  -161,  -161,    56,    83,    79,   175,  -161,  -161,
     177,    75,  -161,   135,  -161,  -161,   175,    29,   121,   200,
     174,  -161,   175,   175,  -161,   175,  -161,  -161,   175,   145,
    -161,    85,   188,  -161,   136,   -29,    -2,  -161,    79,   217,
       9,  -161,    86,     9,  -161,  -161,   175,    50,   175,  -161,
     177,  -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,
     175,   175,  -161,  -161,  -161,  -161,   175,  -161,  -161,  -161,
      67,  -161,     9,   125,   117,    67,  -161,  -161,   217,    56,
    -161,   -29,  -161,  -161,    79,  -161,   175,   130,  -161,     9,
     134,   174,   148,  -161,  -161,  -161,  -161,  -161,   217,  -161,
     103,   125,    45,  -161,  -161,   217,  -161,  -161,  -161,   175,
    -161,  -161,   177,  -161,   104,  -161,   217,   117,  -161,   137,
    -161,  -161,  -161,    45,  -161,   177,  -161,  -161
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     3,     9,     0,     0,     0,     0,     1,    75,    14,
     103,     6,     0,    15,     0,     0,     0,   101,     0,     0,
       4,     2,    32,    66,    54,     0,     0,     0,   102,     0,
       7,    12,     8,    69,     0,     0,    13,    18,     0,   106,
       5,     0,    58,    59,    71,     0,     0,     0,     0,    10,
      69,    67,     0,    31,     0,    27,    26,    25,    24,    46,
      28,    29,    17,    23,    21,    22,     0,     0,    11,    53,
      14,    60,    60,    88,    84,     0,     0,    78,     0,    74,
       0,   113,     0,    77,    98,     0,    39,    45,    47,    48,
      44,    34,     0,    36,    41,    42,    43,     0,     0,    19,
      20,     0,    55,    56,     0,     0,     0,   113,    72,    70,
      69,     0,   120,   121,   119,   114,   113,    94,     0,   108,
     110,   112,   113,   113,    87,   113,    96,    93,   113,   113,
      35,     0,     0,    16,    69,     0,     0,    63,     0,     0,
       0,    92,    94,     0,   105,    73,   113,     0,   113,    89,
      69,   130,   133,   134,   131,   129,   132,   122,   123,   124,
     113,   113,   125,   126,   127,   128,   113,   117,   118,    76,
       0,   100,     0,     0,     0,     0,    33,    68,     0,     0,
      61,     0,    57,    82,     0,    83,   113,     0,   116,     0,
      80,   109,   107,   111,    97,    95,    99,    40,     0,    52,
       0,     0,     0,    65,    62,     0,    91,   104,    85,   113,
     115,    90,    69,    38,     0,    50,     0,     0,    64,     0,
      79,    51,    37,     0,    86,    69,    49,    81
  };

  const short
  parser::yypgoto_[] =
  {
    -161,  -161,  -161,  -161,   164,  -161,    -6,    96,  -161,  -161,
     115,   -16,  -161,   -62,   -49,  -161,  -161,    71,  -161,    39,
    -161,     4,  -121,  -161,  -161,  -161,  -161,   -32,  -161,  -161,
    -161,  -161,  -161,   132,  -161,    42,   -90,   -59,  -161,   -26,
    -161,  -161,  -161,   -18,  -100,  -161,  -161,  -161,   108,  -161,
    -161,  -161,  -161,   -48,  -161,   131,  -160,  -161,    22,   -13,
      -5,   -99,     3,   -72,    91,    93,   -98,  -161,  -161,  -161,
    -161,  -161
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     3,    21,     4,     5,    14,   135,    15,    16,    26,
      38,   114,    63,    64,    65,    66,    67,    24,    35,    91,
      92,   198,    93,    94,    95,    96,   175,   200,    33,    45,
      46,    47,    48,   103,   136,   137,    25,    52,   102,    77,
      50,   109,    78,     9,    79,    80,   209,   225,   125,    81,
     150,   212,   140,   115,   127,   128,   195,    83,   116,    30,
     117,   143,    41,   144,   119,   120,   121,   122,   123,   160,
     166,   161
  };

  const short
  parser::yytable_[] =
  {
      11,    12,    82,    90,    99,   100,    32,    49,    36,   118,
     145,    27,    29,    31,   138,   201,    40,    53,   182,    34,
      31,   108,    62,    10,   167,   168,     1,    69,    70,   170,
     172,    54,    39,    18,    19,    51,    68,     2,   132,     2,
       8,    22,    71,    72,   147,    84,   139,    97,    31,   189,
     190,    56,    57,   169,   221,    28,    23,   203,   141,   -30,
     110,     8,    82,    22,     8,    10,    28,   130,   193,   174,
      39,    28,    23,     7,   187,   111,   178,   213,    23,   -30,
     -30,   -30,   133,    90,   218,    17,   173,   126,    10,   138,
      90,    56,    57,   104,   104,   222,    13,   106,   107,    31,
      17,   142,    82,   -30,   214,    84,   129,    28,   177,    56,
      57,    17,   220,   126,   207,   -94,   171,    37,   179,    42,
      43,    44,   205,   180,   -30,   227,   194,   183,    39,    90,
     185,    20,   181,    31,   188,   124,   206,   219,   215,   148,
     217,   -29,   -29,   184,   126,    84,   186,    51,   149,    90,
      55,    56,    57,    58,    10,    44,    90,   197,   199,   196,
     208,   226,   211,   194,    82,     6,   101,    90,   224,    98,
      59,   176,   134,   186,    31,   186,   210,    82,   202,   142,
      55,    56,    57,    58,    10,   223,    10,   112,    55,    56,
      57,    58,   186,    55,    60,   113,    44,   157,   158,   159,
      59,    17,    28,    73,   105,   216,    74,    84,    59,    86,
      87,    88,    89,    59,    85,    75,    76,   112,    55,   146,
      84,   204,    55,   131,    60,   113,   162,   163,   164,   165,
       0,    17,    60,    61,    86,    87,    88,    89,    59,    87,
      88,    89,    59,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   192,   191
  };

  const short
  parser::yycheck_[] =
  {
       5,     6,    50,    52,    66,    67,    19,    33,    26,    81,
     110,    16,    18,    18,   104,   175,    29,    35,   139,    25,
      25,    20,    38,     9,   122,   123,     1,    45,    46,   128,
     129,    36,    61,    11,    12,    64,    41,    14,    97,    14,
      63,     1,    47,    48,   116,    50,   105,    53,    53,   148,
     150,     6,     7,   125,   214,    57,    16,   178,   106,    19,
      78,    63,   110,     1,    63,     9,    57,    85,   166,   131,
      61,    57,    16,     0,   146,    80,   135,   198,    16,    17,
      18,    19,    98,   132,   205,    56,     1,    58,     9,   179,
     139,     6,     7,    71,    72,   216,    15,    75,    76,   104,
      56,   106,   150,    63,     1,   110,    84,    57,   134,     6,
       7,    56,   212,    58,   186,    60,   129,    47,   136,    17,
      18,    19,   181,   136,    62,   225,    59,   140,    61,   178,
     143,    62,   138,   138,   147,    60,   184,   209,   200,   117,
     202,     6,     7,   140,    58,   150,   143,    64,    27,   198,
       5,     6,     7,     8,     9,    19,   205,    32,    41,   172,
      30,   223,    28,    59,   212,     1,    70,   216,    31,    54,
      25,   132,   101,   170,   179,   172,   189,   225,   175,   184,
       5,     6,     7,     8,     9,   217,     9,    42,     5,     6,
       7,     8,   189,     5,    49,    50,    19,    49,    50,    51,
      25,    56,    57,    26,    72,   201,    29,   212,    25,    21,
      22,    23,    24,    25,     1,    38,    39,    42,     5,   111,
     225,   179,     5,    92,    49,    50,    52,    53,    54,    55,
      -1,    56,    49,    50,    21,    22,    23,    24,    25,    22,
      23,    24,    25,    43,    44,    45,    46,    47,    48,    49,
      50,    51,   161,   160
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
     109,   130,   129,   131,    59,   121,   124,    32,    86,    41,
      92,   121,   127,    87,   100,   102,   118,   128,    30,   111,
     124,    28,   116,    87,     1,    78,    86,    78,    87,   128,
     109,   121,    87,    92,    31,   112,    78,   109
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    65,    66,    66,    67,    68,    68,    68,    68,    69,
      70,    71,    71,    72,    72,    73,    74,    74,    75,    76,
      76,    76,    76,    76,    77,    78,    78,    79,    80,    81,
      82,    82,    82,    83,    83,    83,    84,    84,    84,    85,
      86,    87,    87,    87,    87,    88,    79,    89,    90,    91,
      91,    91,    92,    93,    93,    94,    95,    95,    96,    97,
      98,    98,    99,    99,   100,   100,   101,   102,   103,   104,
     104,   105,   106,   107,   107,   108,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   117,   118,   119,   119,   120,   121,   122,   122,
     122,   123,   124,   125,   126,   126,   127,   128,   128,   129,
     129,   130,   130,   131,   131,   131,   131,   131,   131,   131,
     132,   133,   134,   134,   134,   135,   135,   135,   135,   136,
     136,   136,   136,   136,   136
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     4,     1,     1,     5,     2,     4,     5,     1,
       4,     3,     1,     3,     0,     1,     5,     3,     1,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     1,     5,     3,     4,     1,     6,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       3,     4,     1,     3,     0,     3,     3,     5,     1,     1,
       0,     3,     3,     1,     4,     3,     1,     1,     3,     0,
       3,     1,     1,     3,     1,     1,     3,     1,     1,     6,
       4,     8,     4,     4,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     2,     0,     3,     1,     1,     1,     4,
       3,     1,     1,     1,     3,     1,     1,     3,     1,     3,
       1,     3,     1,     0,     1,     4,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
  };




#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,    88,    88,    93,   101,   107,   110,   113,   119,   135,
     140,   146,   151,   160,   163,   168,   174,   179,   186,   192,
     193,   194,   195,   196,   199,   201,   204,   209,   214,   219,
     224,   225,   228,   245,   251,   258,   274,   277,   282,   291,
     297,   304,   305,   306,   307,   310,   315,   320,   325,   331,
     335,   339,   349,   354,   362,   367,   374,   377,   382,   388,
     394,   395,   404,   409,   419,   422,   428,   434,   439,   444,
     445,   453,   458,   464,   471,   481,   486,   487,   488,   489,
     494,   499,   504,   509,   516,   521,   526,   531,   535,   540,
     545,   551,   566,   585,   595,   596,   601,   605,   610,   614,
     617,   625,   629,   633,   639,   644,   652,   657,   660,   664,
     665,   668,   671,   673,   674,   677,   680,   683,   686,   689,
     694,   699,   704,   708,   712,   718,   722,   726,   730,   735,
     739,   743,   747,   751,   755
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
#line 3461 "yacc_bison.h"

#line 778 "parser.y"

