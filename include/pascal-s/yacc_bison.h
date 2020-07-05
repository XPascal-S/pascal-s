// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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


// First part of user declarations.
#line 4 "parser.y" // lalr1.cc:404

#define YYSTYPE void *
using namespace ast;

#line 41 "yacc_bison.h" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif



# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif


namespace yy {
#line 120 "yacc_bison.h" // lalr1.cc:408

  template <class T, class S = std::vector<T> >
  class stack
  {
  public:
    // Hide our reversed order.
    typedef typename S::reverse_iterator iterator;
    typedef typename S::const_reverse_iterator const_iterator;

    stack ()
      : seq_ ()
    {
      seq_.reserve (200);
    }

    stack (unsigned int n)
      : seq_ (n)
    {}

    inline
    T&
    operator[] (unsigned int i)
    {
      return seq_[seq_.size () - 1 - i];
    }

    inline
    const T&
    operator[] (unsigned int i) const
    {
      return seq_[seq_.size () - 1 - i];
    }

    /// Steal the contents of \a t.
    ///
    /// Close to move-semantics.
    inline
    void
    push (T& t)
    {
      seq_.push_back (T());
      operator[](0).move (t);
    }

    inline
    void
    pop (unsigned int n = 1)
    {
      for (; n; --n)
        seq_.pop_back ();
    }

    void
    clear ()
    {
      seq_.clear ();
    }

    inline
    typename S::size_type
    size () const
    {
      return seq_.size ();
    }

    inline
    const_iterator
    begin () const
    {
      return seq_.rbegin ();
    }

    inline
    const_iterator
    end () const
    {
      return seq_.rend ();
    }

  private:
    stack (const stack&);
    stack& operator= (const stack&);
    /// The wrapped container.
    S seq_;
  };

  /// Present a slice of the top of a stack.
  template <class T, class S = stack<T> >
  class slice
  {
  public:
    slice (const S& stack, unsigned int range)
      : stack_ (stack)
      , range_ (range)
    {}

    inline
    const T&
    operator [] (unsigned int i) const
    {
      return stack_[range_ - i];
    }

  private:
    const S& stack_;
    unsigned int range_;
  };





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
      syntax_error (const std::string& m);
    };

    ///yylex interface
    virtual int yylex(void**) = 0;
    virtual void access_ast(void*) = 0;
    virtual Node* ast_reduce_nodes(int, Type)=0;
    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        KEYWORD = 1,
        STR = 2,
        CHAR = 3,
        REAL = 4,
        INT = 5,
        BOOL = 6,
        IDENT = 7,
        NULLPTR = 9,
        ERRORTOKEN = 10,
        COMMENT = 11,
        LENGTH = 12,
        KEYWORD_PROGRAM = 256,
        KEYWORD_CONST = 257,
        KEYWORD_VAR = 258,
        KEYWORD_PROCEDURE = 259,
        KEYWORD_FUNCTION = 260,
        KEYWORD_BEGIN = 261,
        KEYWORD_END = 262,
        KEYWORD_ARRAY = 263,
        KEYWORD_INTEGER = 264,
        KEYWORD_REAL = 265,
        KEYWORD_BOOLEAN = 266,
        KEYWORD_CHAR = 267,
        KEYWORD_IF = 268,
        KEYWORD_THEN = 269,
        KEYWORD_ELSE = 270,
        KEYWORD_FOR = 271,
        KEYWORD_TO = 272,
        KEYWORD_DO = 273,
        KEYWORD_OF = 274,
        KEYWORD_DIV = 275,
        KEYWORD_MOD = 276,
        KEYWORD_AND = 277,
        KEYWORD_OR = 278,
        KEYWORD_NOT = 279,
        KEYWORD_READ = 280,
        KEYWORD_WRITE = 281,
        KEYWORD_LENGTH = 282,
        MARKER_RANGE = 512,
        MARKER_LOGICNOT = 513,
        MARKER_NEQ = 529,
        MARKER_LE = 530,
        MARKER_GE = 531,
        MARKER_LT = 532,
        MARKER_EQ = 533,
        MARKER_GT = 534,
        MARKER_ADD = 544,
        MARKER_SUB = 545,
        MARKER_LOGICOR = 546,
        MARKER_MUL = 560,
        MARKER_DIV = 561,
        MARKER_MOD = 562,
        MARKER_LOGICAND = 563,
        MARKER_LPAREN = 576,
        MARKER_RPAREN = 577,
        MARKER_LBRACKET = 592,
        MARKER_RBRACKET = 593,
        MARKER_ASSIGN = 608,
        MARKER_COMMA = 609,
        MARKER_DOT = 610,
        MARKER_SEMICOLON = 611,
        MARKER_COLON = 612
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols.
      basic_symbol (typename Base::kind_type t);

      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;


    /// Build a parser object.
    parser ();
    virtual ~parser ();

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

  private:
    /// This class is not copyable.
    parser (const parser&);
    parser& operator= (const parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (int t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const unsigned char yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


#if YYDEBUG
    /// For a symbol, its name in clear.
    static const char* const yytname_[];

  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
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
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

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
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 247,     ///< Last index in yytable_.
      yynnts_ = 72,  ///< Number of nonterminal symbols.
      yyfinal_ = 7, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 65  ///< Number of tokens.
    };


  };



} // yy
#line 629 "yacc_bison.h" // lalr1.cc:408





// User implementation prologue.

#line 637 "yacc_bison.h" // lalr1.cc:412


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



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 704 "yacc_bison.h" // lalr1.cc:479

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
     :yydebug_ (false),
      yycdebug_ (&std::cerr)
#endif
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
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

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
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
      try
        {
          switch (yyn)
            {
  case 2:
#line 84 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ast::Program((ProgramHead*)(yystack_[3].value), (ProgramBody*)(yystack_[1].value));
  access_ast((yylhs.value));
  //printf("finish!\n");
 }
#line 1133 "yacc_bison.h" // lalr1.cc:859
    break;

  case 3:
#line 93 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
 }
#line 1141 "yacc_bison.h" // lalr1.cc:859
    break;

  case 4:
#line 99 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ProgramHead((const ExpKeyword*)(yystack_[4].value), new Ident((const Identifier*)(yystack_[3].value)), (IdentList*)(yystack_[1].value));
}
#line 1149 "yacc_bison.h" // lalr1.cc:859
    break;

  case 5:
#line 102 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ProgramHead((const ExpKeyword*)(yystack_[1].value), new Ident((const Identifier*)(yystack_[0].value)));
}
#line 1157 "yacc_bison.h" // lalr1.cc:859
    break;

  case 6:
#line 105 "parser.y" // lalr1.cc:859
    {
    IdentList* idlist = new IdentList();
  ast::copy_pos_with_check(idlist, (ExpMarker*)(yystack_[1].value));
  ast::copy_pos_with_check(idlist, (ExpMarker*)(yystack_[0].value));
  (yylhs.value) = new ProgramHead((const ExpKeyword*)(yystack_[3].value), new Ident((const Identifier*)(yystack_[2].value)), idlist);
}
#line 1168 "yacc_bison.h" // lalr1.cc:859
    break;

  case 7:
#line 111 "parser.y" // lalr1.cc:859
    {

    pascal_s::Pos* pos = ((Node*)(yystack_[3].value))->visit_pos();
    
    #define cur_node (reinterpret_cast<const ast::ExpKeyword*>((yystack_[3].value)))
    printf("\n program head failed at line:%d column:%d: expect:%s but got error Token\n", pos->line-1,pos->column,convertToString(cur_node->value).c_str());
    #undef  cur_node
    
    yyerrok;
}
#line 1183 "yacc_bison.h" // lalr1.cc:859
    break;

  case 8:
#line 126 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1191 "yacc_bison.h" // lalr1.cc:859
    break;

  case 9:
#line 131 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ProgramBody((ConstDecls*)(yystack_[3].value), (VarDecls*)(yystack_[2].value), (SubprogramDecls*)(yystack_[1].value), (CompoundStatement*)(yystack_[0].value));
}
#line 1199 "yacc_bison.h" // lalr1.cc:859
    break;

  case 10:
#line 137 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  ((IdentList*)(yylhs.value))->idents.push_back((Identifier*)(yystack_[0].value));
  ast::copy_pos_with_check((IdentList*)(yylhs.value), (Identifier*)(yystack_[0].value));
}
#line 1209 "yacc_bison.h" // lalr1.cc:859
    break;

  case 11:
#line 142 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new IdentList();
  ((IdentList*)(yylhs.value))->idents.push_back((Identifier*)(yystack_[0].value));
  ast::copy_pos_with_check((IdentList*)(yylhs.value), (Identifier*)(yystack_[0].value));
}
#line 1219 "yacc_bison.h" // lalr1.cc:859
    break;

  case 12:
#line 151 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
}
#line 1227 "yacc_bison.h" // lalr1.cc:859
    break;

  case 13:
#line 154 "parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 1233 "yacc_bison.h" // lalr1.cc:859
    break;

  case 14:
#line 159 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1241 "yacc_bison.h" // lalr1.cc:859
    break;

  case 15:
#line 165 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[4].value);
  ConstDecl* constDecl = new ConstDecl((const Identifier*)(yystack_[2].value), (Exp*)(yystack_[0].value));
  ((ConstDecls*)(yylhs.value))->decls.push_back(constDecl);
}
#line 1251 "yacc_bison.h" // lalr1.cc:859
    break;

  case 16:
#line 170 "parser.y" // lalr1.cc:859
    {
  ConstDecl* constDecl = new ConstDecl((const Identifier*)(yystack_[2].value), (Exp*)(yystack_[0].value));
  (yylhs.value) = new ConstDecls();
  ((ConstDecls*)(yylhs.value))->decls.push_back(constDecl);
}
#line 1261 "yacc_bison.h" // lalr1.cc:859
    break;

  case 17:
#line 177 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1269 "yacc_bison.h" // lalr1.cc:859
    break;

  case 18:
#line 183 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));}
#line 1275 "yacc_bison.h" // lalr1.cc:859
    break;

  case 19:
#line 184 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));}
#line 1281 "yacc_bison.h" // lalr1.cc:859
    break;

  case 20:
#line 185 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1287 "yacc_bison.h" // lalr1.cc:859
    break;

  case 21:
#line 186 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1293 "yacc_bison.h" // lalr1.cc:859
    break;

  case 22:
#line 187 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1299 "yacc_bison.h" // lalr1.cc:859
    break;

  case 23:
#line 190 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExpConstantBoolean(((const ConstantBoolean*)((yystack_[0].value))));}
#line 1305 "yacc_bison.h" // lalr1.cc:859
    break;

  case 24:
#line 192 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantInteger(((const ConstantInteger*)((yystack_[0].value))));
}
#line 1313 "yacc_bison.h" // lalr1.cc:859
    break;

  case 25:
#line 195 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantReal(((const ConstantReal*)((yystack_[0].value))));
  }
#line 1321 "yacc_bison.h" // lalr1.cc:859
    break;

  case 26:
#line 200 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantChar(((const ConstantChar*)((yystack_[0].value))));
}
#line 1329 "yacc_bison.h" // lalr1.cc:859
    break;

  case 27:
#line 205 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1337 "yacc_bison.h" // lalr1.cc:859
    break;

  case 28:
#line 210 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1345 "yacc_bison.h" // lalr1.cc:859
    break;

  case 29:
#line 215 "parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr;  /* new ExpVoid(); */ }
#line 1351 "yacc_bison.h" // lalr1.cc:859
    break;

  case 30:
#line 216 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
}
#line 1359 "yacc_bison.h" // lalr1.cc:859
    break;

  case 31:
#line 219 "parser.y" // lalr1.cc:859
    {
    printf("\n var declarations parse failed\n");
    yyerrok;
}
#line 1368 "yacc_bison.h" // lalr1.cc:859
    break;

  case 32:
#line 227 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[4].value);
  VarDecl* vdecl = new VarDecl((IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
  ((VarDecls*)(yylhs.value))->decls.push_back(vdecl);
  ast::copy_pos_with_check((VarDecls*)(yylhs.value), vdecl);
}
#line 1379 "yacc_bison.h" // lalr1.cc:859
    break;

  case 33:
#line 233 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new VarDecls();

  VarDecl* vdecl = new VarDecl((IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
  ast::copy_pos_with_check((VarDecls*)(yylhs.value), (IdentList*)(yystack_[2].value));
  ((VarDecls*)(yylhs.value))->decls.push_back(vdecl);
  ast::copy_pos_with_check((VarDecls*)(yylhs.value), vdecl);
}
#line 1392 "yacc_bison.h" // lalr1.cc:859
    break;

  case 34:
#line 241 "parser.y" // lalr1.cc:859
    { 
    pascal_s::Pos* pos = ((Node*)(yystack_[2].value))->visit_pos();
    
    printf("\n var declaration failed at line:%d column:%d: expect:array type but got error Token\n", pos->line,pos->column+pos->length+1);

    yyerrok;
}
#line 1404 "yacc_bison.h" // lalr1.cc:859
    break;

  case 35:
#line 251 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
}
#line 1412 "yacc_bison.h" // lalr1.cc:859
    break;

  case 36:
#line 254 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[3].value);
  ((ArrayTypeSpec*)(yylhs.value))->keyword = ((BasicTypeSpec*)(yystack_[0].value))->keyword;
  ast::copy_pos_with_check((ArrayTypeSpec*)(yylhs.value), ((BasicTypeSpec*)(yystack_[0].value))->keyword);
}
#line 1422 "yacc_bison.h" // lalr1.cc:859
    break;

  case 37:
#line 261 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1430 "yacc_bison.h" // lalr1.cc:859
    break;

  case 38:
#line 266 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1438 "yacc_bison.h" // lalr1.cc:859
    break;

  case 39:
#line 272 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1444 "yacc_bison.h" // lalr1.cc:859
    break;

  case 40:
#line 273 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1450 "yacc_bison.h" // lalr1.cc:859
    break;

  case 41:
#line 274 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1456 "yacc_bison.h" // lalr1.cc:859
    break;

  case 42:
#line 275 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1462 "yacc_bison.h" // lalr1.cc:859
    break;

  case 43:
#line 278 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1470 "yacc_bison.h" // lalr1.cc:859
    break;

  case 44:
#line 283 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1478 "yacc_bison.h" // lalr1.cc:859
    break;

  case 45:
#line 288 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1486 "yacc_bison.h" // lalr1.cc:859
    break;

  case 46:
#line 293 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1494 "yacc_bison.h" // lalr1.cc:859
    break;

  case 47:
#line 299 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[4].value);
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)(yystack_[2].value))->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)(yystack_[0].value))->value)->attr)));
}
#line 1503 "yacc_bison.h" // lalr1.cc:859
    break;

  case 48:
#line 303 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ArrayTypeSpec(nullptr);
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)(yystack_[2].value))->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)(yystack_[0].value))->value)->attr)));
}
#line 1512 "yacc_bison.h" // lalr1.cc:859
    break;

  case 49:
#line 307 "parser.y" // lalr1.cc:859
    {
    pascal_s::Pos* pos = ((Node*)(yystack_[3].value))->visit_pos();
    
    #define cur_node (reinterpret_cast<const ast::ExpMarker*>((yystack_[2].value)))
    printf("\nperiod parse failed at line:%d column:%d: expect: num but got %s\n", pos->line,pos->column+pos->length+1,convertToString(cur_node->value).c_str());
    #undef  cur_node
    
    yyerrok;
}
#line 1526 "yacc_bison.h" // lalr1.cc:859
    break;

  case 50:
#line 317 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1534 "yacc_bison.h" // lalr1.cc:859
    break;

  case 51:
#line 322 "parser.y" // lalr1.cc:859
    {
  if( (yystack_[2].value) == nullptr ){
    (yylhs.value) = new SubprogramDecls();
  }else{
    (yylhs.value) = (yystack_[2].value);
  }
  ((SubprogramDecls*)(yylhs.value))->subprogram.push_back(((Subprogram*)(yystack_[1].value)));
}
#line 1547 "yacc_bison.h" // lalr1.cc:859
    break;

  case 52:
#line 330 "parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr;  }
#line 1553 "yacc_bison.h" // lalr1.cc:859
    break;

  case 53:
#line 335 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Subprogram((SubprogramHead*)(yystack_[2].value), (SubprogramBody*)(yystack_[0].value));
}
#line 1561 "yacc_bison.h" // lalr1.cc:859
    break;

  case 54:
#line 342 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new SubprogramHead((const Keyword*)(yystack_[2].value), (const Identifier*)(yystack_[1].value), (ParamList*)(yystack_[0].value), nullptr);
}
#line 1569 "yacc_bison.h" // lalr1.cc:859
    break;

  case 55:
#line 345 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new SubprogramHead((const Keyword*)(yystack_[4].value), (const Identifier*)(yystack_[3].value), (ParamList*)(yystack_[2].value), (BasicTypeSpec*)(yystack_[0].value));
}
#line 1577 "yacc_bison.h" // lalr1.cc:859
    break;

  case 56:
#line 350 "parser.y" // lalr1.cc:859
    {
  // $$ = new ExpKeyword((const Keyword *)($1));
  (yylhs.value) = (yystack_[0].value);
}
#line 1586 "yacc_bison.h" // lalr1.cc:859
    break;

  case 57:
#line 356 "parser.y" // lalr1.cc:859
    {
  //$$ = new ExpKeyword((const Keyword *)($1));
  (yylhs.value) = (yystack_[0].value);
}
#line 1595 "yacc_bison.h" // lalr1.cc:859
    break;

  case 58:
#line 362 "parser.y" // lalr1.cc:859
    { (yylhs.value) =  nullptr; /* new ParamList(); */  }
#line 1601 "yacc_bison.h" // lalr1.cc:859
    break;

  case 59:
#line 363 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
}
#line 1609 "yacc_bison.h" // lalr1.cc:859
    break;

  case 60:
#line 372 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  ((ParamList*)(yylhs.value))->params.push_back((ParamSpec*)(yystack_[0].value));
  ast::copy_pos_with_check((ParamList*)(yylhs.value), (ParamSpec*)(yystack_[0].value));
}
#line 1619 "yacc_bison.h" // lalr1.cc:859
    break;

  case 61:
#line 377 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamList();
  ((ParamList*)(yylhs.value))->params.push_back((ParamSpec*)(yystack_[0].value));
  ast::copy_pos_with_check((ParamList*)(yylhs.value), (ParamSpec*)(yystack_[0].value));
  }
#line 1629 "yacc_bison.h" // lalr1.cc:859
    break;

  case 62:
#line 387 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamSpec((const Keyword*)(yystack_[3].value), (IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
}
#line 1637 "yacc_bison.h" // lalr1.cc:859
    break;

  case 63:
#line 390 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamSpec(nullptr, (IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
}
#line 1645 "yacc_bison.h" // lalr1.cc:859
    break;

  case 64:
#line 396 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1653 "yacc_bison.h" // lalr1.cc:859
    break;

  case 65:
#line 402 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1661 "yacc_bison.h" // lalr1.cc:859
    break;

  case 66:
#line 407 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new SubprogramBody((ConstDecls*)(yystack_[2].value), (VarDecls*)(yystack_[1].value), (CompoundStatement*)(yystack_[0].value));
}
#line 1669 "yacc_bison.h" // lalr1.cc:859
    break;

  case 67:
#line 412 "parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; }
#line 1675 "yacc_bison.h" // lalr1.cc:859
    break;

  case 68:
#line 413 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new CompoundStatement((StatementList*)(yystack_[1].value));
}
#line 1683 "yacc_bison.h" // lalr1.cc:859
    break;

  case 69:
#line 421 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1691 "yacc_bison.h" // lalr1.cc:859
    break;

  case 70:
#line 426 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
             }
#line 1699 "yacc_bison.h" // lalr1.cc:859
    break;

  case 71:
#line 432 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  if( (yystack_[0].value) != nullptr ){
    ((StatementList*)(yylhs.value))->statement.push_back((Statement*)(yystack_[0].value));
    ast::copy_pos_with_check((StatementList*)(yylhs.value), (Statement*)(yystack_[0].value));
  }
}
#line 1711 "yacc_bison.h" // lalr1.cc:859
    break;

  case 72:
#line 439 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new StatementList();
  if( (yystack_[0].value) != nullptr ){
    ((StatementList*)(yylhs.value))->statement.push_back((Statement*)(yystack_[0].value));
    ast::copy_pos_with_check((StatementList*)(yylhs.value), (Statement*)(yystack_[0].value));
  }
}
#line 1723 "yacc_bison.h" // lalr1.cc:859
    break;

  case 73:
#line 449 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1731 "yacc_bison.h" // lalr1.cc:859
    break;

  case 74:
#line 454 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExecStatement(new ExpAssign((Variable*)(yystack_[2].value), (Exp*)(yystack_[0].value)));}
#line 1737 "yacc_bison.h" // lalr1.cc:859
    break;

  case 75:
#line 455 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExecStatement((Exp*)(yystack_[0].value));}
#line 1743 "yacc_bison.h" // lalr1.cc:859
    break;

  case 76:
#line 456 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1749 "yacc_bison.h" // lalr1.cc:859
    break;

  case 77:
#line 458 "parser.y" // lalr1.cc:859
    {
                                        (yylhs.value) = new IfElseStatement((Exp*)(yystack_[4].value), (Statement*)(yystack_[2].value), (Statement*)(yystack_[0].value));
                                        ast::copy_pos_between_tokens((IfElseStatement*)(yylhs.value), (ExpKeyword*)(yystack_[5].value), (Statement*)(yystack_[0].value));
                                      }
#line 1758 "yacc_bison.h" // lalr1.cc:859
    break;

  case 78:
#line 463 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new IfElseStatement((Exp*)(yystack_[2].value), (Statement*)(yystack_[0].value), nullptr);
  ast::copy_pos_between_tokens((IfElseStatement*)(yylhs.value), (ExpKeyword*)(yystack_[3].value), (Statement*)(yystack_[0].value));
}
#line 1767 "yacc_bison.h" // lalr1.cc:859
    break;

  case 79:
#line 468 "parser.y" // lalr1.cc:859
    {
                                                (yylhs.value) = new ForStatement((const Identifier *)(yystack_[6].value), (Exp*)(yystack_[4].value), (Exp*)(yystack_[2].value), (Statement*)(yystack_[0].value));
                                                ast::copy_pos_between_tokens((ForStatement*)(yylhs.value), (ExpKeyword*)(yystack_[7].value), (Statement*)(yystack_[0].value));
                                              }
#line 1776 "yacc_bison.h" // lalr1.cc:859
    break;

  case 80:
#line 473 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Read((VariableList*)(yystack_[1].value));
  ast::copy_pos_with_check((Read*)(yylhs.value), (VariableList*)(yystack_[1].value));
}
#line 1785 "yacc_bison.h" // lalr1.cc:859
    break;

  case 81:
#line 478 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Write((ExpressionList*)(yystack_[1].value));
  ast::copy_pos_with_check((Write*)(yylhs.value), (ExpressionList*)(yystack_[1].value));
}
#line 1794 "yacc_bison.h" // lalr1.cc:859
    break;

  case 82:
#line 484 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1802 "yacc_bison.h" // lalr1.cc:859
    break;

  case 83:
#line 489 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1810 "yacc_bison.h" // lalr1.cc:859
    break;

  case 84:
#line 494 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
   }
#line 1818 "yacc_bison.h" // lalr1.cc:859
    break;

  case 85:
#line 499 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1826 "yacc_bison.h" // lalr1.cc:859
    break;

  case 86:
#line 503 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1834 "yacc_bison.h" // lalr1.cc:859
    break;

  case 87:
#line 508 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1842 "yacc_bison.h" // lalr1.cc:859
    break;

  case 88:
#line 513 "parser.y" // lalr1.cc:859
    {
   (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
        }
#line 1850 "yacc_bison.h" // lalr1.cc:859
    break;

  case 89:
#line 519 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value) ;
  if( ((Node*)(yystack_[0].value))->type == Type::Ident ){
    Variable* var = new Variable();
    var->id = ((Ident*)(yystack_[0].value))->ident;
    ((Ident*)(yystack_[0].value))->ident = nullptr;
    deleteAST((Ident*)(yystack_[0].value));
    ast::copy_pos_with_check(var, var->id);
    ((VariableList*)(yylhs.value))->params.push_back(var);
    ast::copy_pos_with_check((VariableList*)(yylhs.value), var);
  }else{
    ((VariableList*)(yylhs.value))->params.push_back((Variable*)(yystack_[0].value));
    ast::copy_pos_with_check((VariableList*)(yylhs.value), (Variable*)(yystack_[0].value));
  }
}
#line 1870 "yacc_bison.h" // lalr1.cc:859
    break;

  case 90:
#line 534 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new VariableList();
  if( ((Node*)(yystack_[0].value))->type == Type::Ident ){
    Variable* var = new Variable();
    var->id = ((Ident*)(yystack_[0].value))->ident;
    ((Ident*)(yystack_[0].value))->ident = nullptr;
    deleteAST((Ident*)(yystack_[0].value));
    ast::copy_pos_with_check(var, var->id);
    ((VariableList*)(yylhs.value))->params.push_back(var);
    ast::copy_pos_with_check((VariableList*)(yylhs.value), var);
  }else{
    ((VariableList*)(yylhs.value))->params.push_back((Variable*)(yystack_[0].value));
    ast::copy_pos_with_check((VariableList*)(yylhs.value), (Variable*)(yystack_[0].value));
  }
}
#line 1890 "yacc_bison.h" // lalr1.cc:859
    break;

  case 91:
#line 553 "parser.y" // lalr1.cc:859
    {
  if( (yystack_[0].value) == nullptr ){
    (yylhs.value) = new Ident((Identifier*)(yystack_[1].value));
    }else{
    (yylhs.value) = new Variable((Identifier*)(yystack_[1].value), (ExpressionList*)(yystack_[0].value));
    ast::copy_pos_between_tokens((Variable*)(yylhs.value), (Identifier*)(yystack_[1].value), (ExpressionList*)(yystack_[0].value));
  }
}
#line 1903 "yacc_bison.h" // lalr1.cc:859
    break;

  case 92:
#line 563 "parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; /* new ExpressionList(); */ }
#line 1909 "yacc_bison.h" // lalr1.cc:859
    break;

  case 93:
#line 564 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
}
#line 1917 "yacc_bison.h" // lalr1.cc:859
    break;

  case 94:
#line 569 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1925 "yacc_bison.h" // lalr1.cc:859
    break;

  case 95:
#line 573 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1933 "yacc_bison.h" // lalr1.cc:859
    break;

  case 96:
#line 578 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new Ident((const Identifier*)(yystack_[0].value));
  //$$ = new ExpCall((const Identifier*)$1, nullptr);
}
#line 1942 "yacc_bison.h" // lalr1.cc:859
    break;

  case 97:
#line 582 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpCall((const Identifier*)(yystack_[3].value), (ExpressionList*)(yystack_[1].value));
}
#line 1950 "yacc_bison.h" // lalr1.cc:859
    break;

  case 98:
#line 585 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpCall((const Identifier*)(yystack_[2].value), nullptr);
}
#line 1958 "yacc_bison.h" // lalr1.cc:859
    break;

  case 99:
#line 593 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1966 "yacc_bison.h" // lalr1.cc:859
    break;

  case 100:
#line 597 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1974 "yacc_bison.h" // lalr1.cc:859
    break;

  case 101:
#line 601 "parser.y" // lalr1.cc:859
    {
  // $$ = new Ident((const Identifier *)($1));
  (yylhs.value) = (yystack_[0].value);
}
#line 1983 "yacc_bison.h" // lalr1.cc:859
    break;

  case 102:
#line 607 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  ((ExpressionList*)(yylhs.value))->explist.push_back((Exp*)(yystack_[0].value));
  ast::copy_pos_with_check((ExpressionList*)(yylhs.value), (Exp*)(yystack_[0].value));
}
#line 1993 "yacc_bison.h" // lalr1.cc:859
    break;

  case 103:
#line 612 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpressionList();
  ((ExpressionList*)(yylhs.value))->explist.push_back((Exp*)(yystack_[0].value));
  ast::copy_pos_with_check((ExpressionList*)(yylhs.value), (Exp*)(yystack_[0].value));
}
#line 2003 "yacc_bison.h" // lalr1.cc:859
    break;

  case 104:
#line 620 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2011 "yacc_bison.h" // lalr1.cc:859
    break;

  case 105:
#line 625 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2019 "yacc_bison.h" // lalr1.cc:859
    break;

  case 106:
#line 628 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2025 "yacc_bison.h" // lalr1.cc:859
    break;

  case 107:
#line 632 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value)); }
#line 2031 "yacc_bison.h" // lalr1.cc:859
    break;

  case 108:
#line 633 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2037 "yacc_bison.h" // lalr1.cc:859
    break;

  case 109:
#line 636 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2045 "yacc_bison.h" // lalr1.cc:859
    break;

  case 110:
#line 639 "parser.y" // lalr1.cc:859
    { (yylhs.value)=(yystack_[0].value); }
#line 2051 "yacc_bison.h" // lalr1.cc:859
    break;

  case 112:
#line 642 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
}
#line 2059 "yacc_bison.h" // lalr1.cc:859
    break;

  case 113:
#line 645 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpCall((const Identifier*)(yystack_[3].value), (ExpressionList*)(yystack_[1].value));
}
#line 2067 "yacc_bison.h" // lalr1.cc:859
    break;

  case 114:
#line 648 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
}
#line 2075 "yacc_bison.h" // lalr1.cc:859
    break;

  case 115:
#line 651 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2083 "yacc_bison.h" // lalr1.cc:859
    break;

  case 116:
#line 654 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2091 "yacc_bison.h" // lalr1.cc:859
    break;

  case 117:
#line 657 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
  }
#line 2099 "yacc_bison.h" // lalr1.cc:859
    break;

  case 118:
#line 662 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2107 "yacc_bison.h" // lalr1.cc:859
    break;

  case 119:
#line 666 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2115 "yacc_bison.h" // lalr1.cc:859
    break;

  case 120:
#line 670 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2123 "yacc_bison.h" // lalr1.cc:859
    break;

  case 121:
#line 673 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2131 "yacc_bison.h" // lalr1.cc:859
    break;

  case 122:
#line 676 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2139 "yacc_bison.h" // lalr1.cc:859
    break;

  case 123:
#line 681 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2147 "yacc_bison.h" // lalr1.cc:859
    break;

  case 124:
#line 684 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2155 "yacc_bison.h" // lalr1.cc:859
    break;

  case 125:
#line 687 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2163 "yacc_bison.h" // lalr1.cc:859
    break;

  case 126:
#line 690 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2171 "yacc_bison.h" // lalr1.cc:859
    break;

  case 127:
#line 694 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2179 "yacc_bison.h" // lalr1.cc:859
    break;

  case 128:
#line 697 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2187 "yacc_bison.h" // lalr1.cc:859
    break;

  case 129:
#line 700 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2195 "yacc_bison.h" // lalr1.cc:859
    break;

  case 130:
#line 703 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2203 "yacc_bison.h" // lalr1.cc:859
    break;

  case 131:
#line 706 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2211 "yacc_bison.h" // lalr1.cc:859
    break;

  case 132:
#line 709 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2219 "yacc_bison.h" // lalr1.cc:859
    break;


#line 2223 "yacc_bison.h" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -111;

  const signed char parser::yytable_ninf_ = -93;

  const short int
  parser::yypact_[] =
  {
      37,    -7,  -111,    27,   -22,    62,    62,  -111,  -111,    32,
    -111,    42,    42,  -111,    44,    38,    62,  -111,    19,    53,
    -111,  -111,  -111,  -111,  -111,    62,   -22,    67,  -111,     2,
    -111,  -111,  -111,   225,    23,   -22,    62,  -111,   113,  -111,
    -111,    62,  -111,  -111,  -111,   -22,   -22,    62,    62,  -111,
     176,  -111,   198,    62,    67,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,    82,    82,  -111,  -111,
      32,    42,    42,  -111,  -111,    42,    42,  -111,    -2,  -111,
      62,   151,    56,  -111,   111,   -22,  -111,  -111,  -111,  -111,
    -111,  -111,    68,  -111,  -111,  -111,  -111,    23,   113,  -111,
    -111,    34,  -111,  -111,    21,    70,    62,   151,  -111,  -111,
     176,    56,  -111,   116,  -111,  -111,   151,    73,   114,   190,
     134,  -111,   151,   151,  -111,   151,  -111,  -111,   151,   141,
    -111,    82,   207,  -111,   125,    23,   -31,  -111,    62,    55,
       2,  -111,    68,     2,  -111,  -111,   151,    53,   151,  -111,
     176,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
     151,   151,  -111,  -111,  -111,  -111,   151,  -111,  -111,  -111,
      52,  -111,     2,   110,    52,  -111,  -111,    55,    21,  -111,
      23,  -111,  -111,    62,  -111,   151,   122,  -111,     2,   126,
     134,   175,  -111,  -111,  -111,  -111,  -111,    58,   138,    82,
    -111,  -111,    55,  -111,  -111,  -111,   151,  -111,  -111,   176,
    -111,  -111,    82,  -111,    55,   110,  -111,   143,  -111,   171,
    -111,    82,  -111,   176,  -111,  -111,  -111
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
       0,    98,     0,     0,     0,    32,    66,     0,     0,    59,
       0,    55,    80,     0,    81,   111,     0,   114,     0,    78,
     107,   105,   109,    95,    93,    97,    50,     0,     0,     0,
      63,    60,     0,    89,   102,    83,   111,   113,    88,    67,
     119,    48,     0,    38,     0,     0,    62,     0,    77,     0,
      36,     0,    84,    67,    49,    47,    79
  };

  const short int
  parser::yypgoto_[] =
  {
    -111,  -111,  -111,  -111,   179,  -111,    -1,   107,  -111,  -111,
     127,   -26,  -111,   -57,   -49,  -111,  -111,    91,  -111,    64,
    -111,  -111,  -110,  -111,  -111,  -111,  -111,   -21,  -111,  -111,
    -111,  -111,  -111,   136,  -111,    28,   -85,   -89,  -111,   -27,
    -111,  -111,  -111,   -12,  -106,  -111,  -111,  -111,    99,  -111,
    -111,  -111,  -111,   -48,  -111,   124,    43,  -111,    10,    -4,
      -5,   -33,    39,   -76,    84,    86,   -54,  -111,    50,  -111,
    -111,  -111
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     3,    21,     4,     5,    14,   135,    15,    16,    26,
      38,   114,    63,    64,    65,    66,    67,    24,    35,    91,
      92,   214,    93,    94,    95,    96,   174,   197,    33,    45,
      46,    47,    48,   103,   136,   137,    25,    52,   102,    77,
      50,   109,    78,     9,    79,    80,   206,   223,   125,    81,
     150,   209,   140,   115,   127,   128,   194,    83,   116,    30,
     117,   143,    41,   144,   119,   120,   121,   122,   123,   160,
     166,   161
  };

  const short int
  parser::yytable_[] =
  {
      11,    12,    82,    90,   145,   118,    49,     2,   132,    99,
     100,    27,    62,    31,    36,    32,   139,    29,   108,   138,
      31,    18,    19,    53,    34,    40,    28,     7,    10,   181,
      10,    54,     8,    69,    70,    22,    68,    23,     1,    22,
     147,     8,    71,    72,   189,    84,   177,    13,    31,   169,
      23,     2,    97,   -29,    23,   -29,   -29,   -29,   141,    28,
      55,     8,    82,    39,    56,    57,   110,   200,   167,   168,
     186,    10,   133,   130,   173,   111,    28,    87,    88,    89,
      59,   104,   104,    90,    39,   106,   107,    51,    56,    57,
      90,   202,   216,   138,   129,   170,   172,   -29,    17,    31,
     -29,   142,    82,   218,   220,    84,    20,   176,   210,   204,
      28,   193,   192,    39,    37,   188,   124,   226,    55,    56,
      57,    58,   -28,   -28,   178,   171,   126,   148,    90,    17,
     217,   126,   179,    31,    51,   203,   182,   180,    59,   184,
     211,   149,   215,   187,    44,    84,    55,    56,    57,    58,
      10,   196,   205,    90,   208,   219,    55,    56,    57,    58,
      10,    82,    60,    61,   225,    90,    59,    17,   195,   126,
     213,   -92,   224,    31,   222,    82,    59,   101,   142,   183,
       6,    98,   185,   112,   207,    10,   162,   163,   164,   165,
      60,   113,   134,   112,   221,    44,   175,    17,    28,    85,
      60,   113,    73,    55,    84,    74,   201,    17,   105,   185,
     146,   185,    55,   199,    75,    76,   131,   198,    84,    86,
      87,    88,    89,    59,   157,   158,   159,   185,    86,    87,
      88,    89,    59,   151,   152,   153,   154,   155,   156,   157,
     158,   159,    42,    43,    44,   191,   190,   212
  };

  const unsigned char
  parser::yycheck_[] =
  {
       5,     6,    50,    52,   110,    81,    33,    14,    97,    66,
      67,    16,    38,    18,    26,    19,   105,    18,    20,   104,
      25,    11,    12,    35,    25,    29,    57,     0,     9,   139,
       9,    36,    63,    45,    46,     1,    41,    16,     1,     1,
     116,    63,    47,    48,   150,    50,   135,    15,    53,   125,
      16,    14,    53,    19,    16,    17,    18,    19,   106,    57,
       5,    63,   110,    61,     6,     7,    78,   177,   122,   123,
     146,     9,    98,    85,   131,    80,    57,    22,    23,    24,
      25,    71,    72,   132,    61,    75,    76,    64,     6,     7,
     139,   180,   202,   178,    84,   128,   129,    63,    56,   104,
      62,   106,   150,   209,   214,   110,    62,   134,    50,   185,
      57,    59,   166,    61,    47,   148,    60,   223,     5,     6,
       7,     8,     6,     7,   136,   129,    58,   117,   177,    56,
     206,    58,   136,   138,    64,   183,   140,   138,    25,   143,
     197,    27,   199,   147,    19,   150,     5,     6,     7,     8,
       9,    41,    30,   202,    28,   212,     5,     6,     7,     8,
       9,   209,    49,    50,   221,   214,    25,    56,   172,    58,
      32,    60,     1,   178,    31,   223,    25,    70,   183,   140,
       1,    54,   143,    42,   188,     9,    52,    53,    54,    55,
      49,    50,   101,    42,   215,    19,   132,    56,    57,     1,
      49,    50,    26,     5,   209,    29,   178,    56,    72,   170,
     111,   172,     5,   174,    38,    39,    92,   174,   223,    21,
      22,    23,    24,    25,    49,    50,    51,   188,    21,    22,
      23,    24,    25,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    17,    18,    19,   161,   160,   197
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
     126,   124,   126,    78,    91,    84,   104,   102,   108,   124,
      71,    87,   124,   127,   124,   127,   128,   124,   126,   109,
     130,   129,   131,    59,   121,   124,    41,    92,   121,   127,
      87,   100,   102,   118,   128,    30,   111,   124,    28,   116,
      50,    78,   133,    32,    86,    78,    87,   128,   109,    78,
      87,    92,    31,   112,     1,    78,   109
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

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     4,     1,     5,     2,     4,     5,     1,     4,
       3,     1,     3,     0,     1,     5,     3,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       3,     1,     5,     3,     4,     1,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     3,     5,
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
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "KEYWORD", "STR", "CHAR", "REAL", "INT",
  "BOOL", "IDENT", "NULLPTR", "ERRORTOKEN", "COMMENT", "LENGTH",
  "KEYWORD_PROGRAM", "KEYWORD_CONST", "KEYWORD_VAR", "KEYWORD_PROCEDURE",
  "KEYWORD_FUNCTION", "KEYWORD_BEGIN", "KEYWORD_END", "KEYWORD_ARRAY",
  "KEYWORD_INTEGER", "KEYWORD_REAL", "KEYWORD_BOOLEAN", "KEYWORD_CHAR",
  "KEYWORD_IF", "KEYWORD_THEN", "KEYWORD_ELSE", "KEYWORD_FOR",
  "KEYWORD_TO", "KEYWORD_DO", "KEYWORD_OF", "KEYWORD_DIV", "KEYWORD_MOD",
  "KEYWORD_AND", "KEYWORD_OR", "KEYWORD_NOT", "KEYWORD_READ",
  "KEYWORD_WRITE", "KEYWORD_LENGTH", "MARKER_RANGE", "MARKER_LOGICNOT",
  "MARKER_NEQ", "MARKER_LE", "MARKER_GE", "MARKER_LT", "MARKER_EQ",
  "MARKER_GT", "MARKER_ADD", "MARKER_SUB", "MARKER_LOGICOR", "MARKER_MUL",
  "MARKER_DIV", "MARKER_MOD", "MARKER_LOGICAND", "MARKER_LPAREN",
  "MARKER_RPAREN", "MARKER_LBRACKET", "MARKER_RBRACKET", "MARKER_ASSIGN",
  "MARKER_COMMA", "MARKER_DOT", "MARKER_SEMICOLON", "MARKER_COLON",
  "$accept", "programstruct", "dot", "program_head", "program",
  "program_body", "idlist", "const_declarations", "const",
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


  const unsigned short int
  parser::yyrline_[] =
  {
       0,    84,    84,    93,    99,   102,   105,   111,   126,   131,
     137,   142,   151,   154,   159,   165,   170,   177,   183,   184,
     185,   186,   187,   190,   192,   195,   200,   205,   210,   215,
     216,   219,   227,   233,   241,   251,   254,   261,   266,   272,
     273,   274,   275,   278,   283,   288,   293,   299,   303,   307,
     317,   322,   330,   335,   342,   345,   350,   356,   362,   363,
     372,   377,   387,   390,   396,   402,   407,   412,   413,   421,
     426,   432,   439,   449,   454,   455,   456,   457,   462,   467,
     472,   477,   484,   489,   494,   499,   503,   508,   513,   519,
     534,   553,   563,   564,   569,   573,   578,   582,   585,   593,
     597,   601,   607,   612,   620,   625,   628,   632,   633,   636,
     639,   641,   642,   645,   648,   651,   654,   657,   662,   666,
     670,   673,   676,   681,   684,   687,   690,   694,   697,   700,
     703,   706,   709
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
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
    const unsigned int user_token_number_max_ = 614;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2766 "yacc_bison.h" // lalr1.cc:1167
#line 712 "parser.y" // lalr1.cc:1168


