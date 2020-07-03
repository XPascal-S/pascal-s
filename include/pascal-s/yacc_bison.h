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

#line 40 "yacc_bison.h" // lalr1.cc:404

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
#line 119 "yacc_bison.h" // lalr1.cc:408

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
        LENGTH = 10,
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
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

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
      yylast_ = 203,     ///< Last index in yytable_.
      yynnts_ = 73,  ///< Number of nonterminal symbols.
      yyfinal_ = 5, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 63  ///< Number of tokens.
    };


  };



} // yy
#line 626 "yacc_bison.h" // lalr1.cc:408





// User implementation prologue.

#line 634 "yacc_bison.h" // lalr1.cc:412


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
#line 701 "yacc_bison.h" // lalr1.cc:479

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
#line 82 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Program((ProgramHead*)(yystack_[3].value), (ProgramBody*)(yystack_[1].value));
  // printf("%x %d %d\n", $$, ((Program*)$$)->type, ((Node*)$$)->type);
  access_ast((yylhs.value));
  /* Program *node = reinterpret_cast<Program*> (ast_reduce_nodes(4, Type::Program)); */
  /* node->programHead = (ProgramHead*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop semicolon */
  /* node->programBody = (ProgramBody*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop dot */
 }
#line 1137 "yacc_bison.h" // lalr1.cc:859
    break;

  case 3:
#line 99 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
 }
#line 1145 "yacc_bison.h" // lalr1.cc:859
    break;

  case 4:
#line 105 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ProgramHead((const ExpKeyword*)(yystack_[4].value), (Ident*)(yystack_[3].value), (IdentList*)(yystack_[1].value));
  /* ProgramHead *node = reinterpret_cast<ProgramHead *>(ast_reduce_nodes(5, Type::ProgramHead)); */
  /* node->programKeyword = (const ExpKeyword*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->id = (Ident*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front(); //pop lparen */
  /* node->idlist = ( IdentList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop rparen */
}
#line 1162 "yacc_bison.h" // lalr1.cc:859
    break;

  case 5:
#line 117 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ProgramHead((const ExpKeyword*)(yystack_[1].value), (Ident*)(yystack_[0].value));
  /* ProgramHead *node = reinterpret_cast<ProgramHead *>(ast_reduce_nodes(2, Type::ProgramHead)); */
  /* node->programKeyword = ( ExpKeyword*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->id = ( Ident*)(node->children.front()); */
  /* node->children.pop_front(); */
}
#line 1175 "yacc_bison.h" // lalr1.cc:859
    break;

  case 6:
#line 129 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1183 "yacc_bison.h" // lalr1.cc:859
    break;

  case 7:
#line 134 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ProgramBody((ConstDecls*)(yystack_[3].value), (VarDecls*)(yystack_[2].value), (SubprogramDecls*)(yystack_[1].value), (CompoundStatement*)(yystack_[0].value));
  /* ProgramBody *node = reinterpret_cast<ProgramBody*> (ast_reduce_nodes(4, Type::ProgramBody)); */

  /* node->constdecls = (ConstDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->vardecls = (VarDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->subprogram = (SubprogramDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->compound = (CompoundStatement*)(node->children.front()); */
  /* node->children.pop_front(); */
}
#line 1204 "yacc_bison.h" // lalr1.cc:859
    break;

  case 8:
#line 153 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  ((IdentList*)(yylhs.value))->idents.push_back((Identifier*)(yystack_[0].value));
  /* IdentList* node = reinterpret_cast<IdentList*> (ast_reduce_nodes(3, Type::IdentList)); */
  /* node->idents = reinterpret_cast<IdentList*>(node->children.front())->idents; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop comma */
  /* Identifier* id = (Identifier*)(node->children.front()); */
  /* node->idents.push_back(id); */
  /* node->children.pop_front(); */
}
#line 1220 "yacc_bison.h" // lalr1.cc:859
    break;

  case 9:
#line 164 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new IdentList();
  ((IdentList*)(yylhs.value))->idents.push_back((Identifier*)(yystack_[0].value));
  /* IdentList* node = reinterpret_cast<IdentList*> (ast_reduce_nodes(1, Type::IdentList)); */
  /* Identifier* id = (Identifier*)(node->children.front()); */
  /* node->idents.push_back(id); */
  /* node->children.pop_front(); */
  }
#line 1233 "yacc_bison.h" // lalr1.cc:859
    break;

  case 10:
#line 176 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
  /* ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(3, Type::ConstDecls)); */
  /* node->children.pop_front();// pop const */
  /* node->decls = reinterpret_cast<ConstDecls*>(node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */
}
#line 1246 "yacc_bison.h" // lalr1.cc:859
    break;

  case 11:
#line 184 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ConstDecls(); }
#line 1252 "yacc_bison.h" // lalr1.cc:859
    break;

  case 12:
#line 189 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1260 "yacc_bison.h" // lalr1.cc:859
    break;

  case 13:
#line 195 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[4].value);
  ConstDecl* constDecl = new ConstDecl((const Identifier*)(yystack_[2].value), (Exp*)(yystack_[0].value));
  ((ConstDecls*)(yylhs.value))->decls.push_back(constDecl);
  /* ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(5, Type::ConstDecls)); */

  /* node->decls = reinterpret_cast<ConstDecls*> (node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */

  /* Identifier* id = (Identifier*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop eq */
  /* Exp* rhs = (Exp*)(node->children.front()); */
  /* ConstDecl* constDecl = new ConstDecl(id, rhs); */
  /* // constDecl->ident = ; */
  /* // constDecl->rhs = ; */
  /* node->decls.push_back(constDecl); */
  /* node->children.pop_front(); */
}
#line 1285 "yacc_bison.h" // lalr1.cc:859
    break;

  case 14:
#line 215 "parser.y" // lalr1.cc:859
    {
  ConstDecl* constDecl = new ConstDecl((const Identifier*)(yystack_[2].value), (Exp*)(yystack_[0].value));
  (yylhs.value) = new ConstDecls();
  ((ConstDecls*)(yylhs.value))->decls.push_back(constDecl);
  /* ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(3, Type::ConstDecls)); */

  /* Identifier* ident = (Identifier*)(node->children.front()); */
  /* // const->ident = (Identifier*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop eq */
  /* // const->rhs = (Exp*)(node->children.front()); */
  /* Exp* rhs = (Exp*)(node->children.front()); */

  /* ConstDecl* constDecl = new ConstDecl(ident, rhs); */
  /* printf("\n\nget constDecls\n\n"); */
  /* node->children.pop_front(); */
  /* printf("\n\n pop front \n\n"); */
  /* node->decls.push_back(constDecl); */
  /* printf("%d\n\n", node->decls.size()); */
  /* printf("\n\n push back \n\n"); */
}
#line 1311 "yacc_bison.h" // lalr1.cc:859
    break;

  case 15:
#line 239 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1319 "yacc_bison.h" // lalr1.cc:859
    break;

  case 16:
#line 245 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));}
#line 1325 "yacc_bison.h" // lalr1.cc:859
    break;

  case 17:
#line 246 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));}
#line 1331 "yacc_bison.h" // lalr1.cc:859
    break;

  case 18:
#line 247 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1337 "yacc_bison.h" // lalr1.cc:859
    break;

  case 19:
#line 248 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1343 "yacc_bison.h" // lalr1.cc:859
    break;

  case 20:
#line 249 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1349 "yacc_bison.h" // lalr1.cc:859
    break;

  case 21:
#line 252 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExpConstantBoolean(((const ConstantBoolean*)((yystack_[0].value))));}
#line 1355 "yacc_bison.h" // lalr1.cc:859
    break;

  case 22:
#line 254 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantInteger(((const ConstantInteger*)((yystack_[0].value))));
}
#line 1363 "yacc_bison.h" // lalr1.cc:859
    break;

  case 23:
#line 259 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantChar(((const ConstantChar*)((yystack_[0].value))));
}
#line 1371 "yacc_bison.h" // lalr1.cc:859
    break;

  case 24:
#line 264 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1379 "yacc_bison.h" // lalr1.cc:859
    break;

  case 25:
#line 269 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1387 "yacc_bison.h" // lalr1.cc:859
    break;

  case 26:
#line 274 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ExpVoid();  /*  */ }
#line 1393 "yacc_bison.h" // lalr1.cc:859
    break;

  case 27:
#line 275 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
  /* VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(3, Type::VarDecls)); */
  /* node->children.pop_front();// pop var */
  /* node->decls = reinterpret_cast<VarDecls*>(node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */
}
#line 1406 "yacc_bison.h" // lalr1.cc:859
    break;

  case 28:
#line 287 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[4].value);
  VarDecl* vdecl = new VarDecl((IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
  ((VarDecls*)(yylhs.value))->decls.push_back(vdecl);
  /* VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(5, Type::VarDecls)); */

  /* node->decls = reinterpret_cast<VarDecls*>(node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */

  /* IdentList* idents = (IdentList*)(node->children.front()); */
  /* // const->idents = (IdentList*)(node->children.front()); */
  /* node->children.pop_front(); // idlist */
  /* node->children.pop_front(); // pop colon */
  /* // const->type_spec = (TypeSpec*)(node->children.front()); */
  /* TypeSpec* type_spec = (TypeSpec*)(node->children.front()); */
  /* VarDecl* varDecl = new VarDecl(idents, type_spec); */
  /* node->decls.push_back(varDecl); */

  /* node->children.pop_front(); */
}
#line 1432 "yacc_bison.h" // lalr1.cc:859
    break;

  case 29:
#line 308 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new VarDecls();
  VarDecl* vdecl = new VarDecl((IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
  ((VarDecls*)(yylhs.value))->decls.push_back(vdecl);
  /* VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(3, Type::VarDecls)); */

  /* // const->idents = (IdentList*)(node->children.front()); */
  /* IdentList* idents = (IdentList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop colon */
  /* // const->type_spec = (TypeSpec*)(node->children.front()); */
  /* TypeSpec* type_spec = (TypeSpec*)(node->children.front()); */

  /* node->children.pop_front(); *
     /
     /* VarDecl* varDecl = new VarDecl(idents, type_spec); */
  /* node->decls.push_back(varDecl); */
}
#line 1455 "yacc_bison.h" // lalr1.cc:859
    break;

  case 30:
#line 330 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
}
#line 1463 "yacc_bison.h" // lalr1.cc:859
    break;

  case 31:
#line 333 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[3].value);
  ((ArrayTypeSpec*)(yylhs.value))->keyword = ((BasicTypeSpec*)(yystack_[0].value))->keyword;
}
#line 1472 "yacc_bison.h" // lalr1.cc:859
    break;

  case 32:
#line 339 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1480 "yacc_bison.h" // lalr1.cc:859
    break;

  case 33:
#line 344 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1488 "yacc_bison.h" // lalr1.cc:859
    break;

  case 34:
#line 350 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1494 "yacc_bison.h" // lalr1.cc:859
    break;

  case 35:
#line 351 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1500 "yacc_bison.h" // lalr1.cc:859
    break;

  case 36:
#line 352 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1506 "yacc_bison.h" // lalr1.cc:859
    break;

  case 37:
#line 353 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1512 "yacc_bison.h" // lalr1.cc:859
    break;

  case 38:
#line 356 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1520 "yacc_bison.h" // lalr1.cc:859
    break;

  case 39:
#line 361 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1528 "yacc_bison.h" // lalr1.cc:859
    break;

  case 40:
#line 366 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1536 "yacc_bison.h" // lalr1.cc:859
    break;

  case 41:
#line 371 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1544 "yacc_bison.h" // lalr1.cc:859
    break;

  case 42:
#line 377 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[4].value);
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)(yystack_[2].value), (int64_t)(yystack_[0].value)));
  //ast_reduce_nodes(5, Type::ArrayTypeSpec);
}
#line 1554 "yacc_bison.h" // lalr1.cc:859
    break;

  case 43:
#line 382 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ArrayTypeSpec();
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)(yystack_[2].value), (int64_t)(yystack_[0].value)));
  //ast_reduce_nodes(3, Type::ArrayTypeSpec);
}
#line 1564 "yacc_bison.h" // lalr1.cc:859
    break;

  case 44:
#line 388 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1572 "yacc_bison.h" // lalr1.cc:859
    break;

  case 45:
#line 393 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  ((SubprogramDecls*)(yylhs.value))->subprogram.push_back(((Subprogram*)(yystack_[1].value)));
  /* SubprogramDecls* node = reinterpret_cast<SubprogramDecls*> (ast_reduce_nodes(3, Type::SubprogramDecls)); */

  /* node->subprogram = reinterpret_cast<SubprogramDecls*>(node->children.front())->subprogram; */
  /* node->children.pop_front(); */

  /* Subprogram* sub = (Subprogram*)(node->children.front()); */
  /* node->subprogram.push_back(sub); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */

  //ast_reduce_nodes(3, Type::SubprogramDecls);
}
#line 1592 "yacc_bison.h" // lalr1.cc:859
    break;

  case 46:
#line 408 "parser.y" // lalr1.cc:859
    { printf("\n\nvoid sub decl\n\n"); (yylhs.value) = new SubprogramDecls();  }
#line 1598 "yacc_bison.h" // lalr1.cc:859
    break;

  case 47:
#line 413 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Subprogram((SubprogramHead*)(yystack_[2].value), (SubprogramBody*)(yystack_[0].value));
  /* Subprogram* node = reinterpret_cast<Subprogram*> (ast_reduce_nodes(3, Type::Subprogram)); */
  /* node->subhead = (SubprogramHead*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */
  /* node->subbody = (SubprogramBody*)(node->children.front()); */
  /* node->children.pop_front(); */
}
#line 1612 "yacc_bison.h" // lalr1.cc:859
    break;

  case 48:
#line 426 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new SubprogramHead((const Keyword*)(yystack_[2].value), (const Identifier*)(yystack_[1].value), (ParamList*)(yystack_[0].value), nullptr);
  /* SubprogramHead* node = reinterpret_cast<SubprogramHead*> (ast_reduce_nodes(3, Type::SubprogramHead)); */


  /*  node->children.pop_front();// pop procedure */
  /*  // pro->name = (Identifier*)(node->children.front()); */
  /*  Identifier* name = (Identifier*)(node->children.front()); */
  /*  node->children.pop_front(); */
  /*  // pro->decls = (ParamList*)(node->children.front()); */
  /*  ParamList* decls = (ParamList*)(node->children.front()); */
  /*  node->children.pop_front(); */

  /*  Procedure* pro = new Procedure(name, decls); */
  /*  node->proc = pro; */
}
#line 1633 "yacc_bison.h" // lalr1.cc:859
    break;

  case 49:
#line 442 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new SubprogramHead((const Keyword*)(yystack_[4].value), (const Identifier*)(yystack_[3].value), (ParamList*)(yystack_[2].value), (BasicTypeSpec*)(yystack_[0].value));
  /* SubprogramHead* node = reinterpret_cast<SubprogramHead*> (ast_reduce_nodes(5, Type::SubprogramHead)); */

  /* FunctionDecl* func = new FunctionDecl(); */
  /* node->children.pop_front();// pop function */
  /* func->name = (Identifier*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* func->decls = (ParamList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop colon */
  /* func->basic = (BasicTypeSpec*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->func = func; */
}
#line 1654 "yacc_bison.h" // lalr1.cc:859
    break;

  case 50:
#line 460 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1662 "yacc_bison.h" // lalr1.cc:859
    break;

  case 51:
#line 465 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1670 "yacc_bison.h" // lalr1.cc:859
    break;

  case 52:
#line 470 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ParamList();  /*  */  }
#line 1676 "yacc_bison.h" // lalr1.cc:859
    break;

  case 53:
#line 471 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(3, Type::ParamList)); */
  /* node->children.pop_front();//pop lparen */
  /* node->params = reinterpret_cast<ParamList*>(node->children.front())->params; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop rparen */
  //ast_reduce_nodes(3, Type::ParamList);
}
#line 1690 "yacc_bison.h" // lalr1.cc:859
    break;

  case 54:
#line 486 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  ((ParamList*)(yylhs.value))->params.push_back((ParamSpec*)(yystack_[0].value));
  /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(3, Type::ParamList)); */
  /* node->params = reinterpret_cast<ParamList*>(node->children.front())->params; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */

  /* ParamSpec* param = (ParamSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->params.push_back(param); */
}
#line 1707 "yacc_bison.h" // lalr1.cc:859
    break;

  case 55:
#line 498 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamList();
  ((ParamList*)(yylhs.value))->params.push_back((ParamSpec*)(yystack_[0].value));
  /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(1, Type::ParamList)); */
  /* ParamSpec* param = (ParamSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->params.push_back(param); */
  //$$ = $1;
  }
#line 1721 "yacc_bison.h" // lalr1.cc:859
    break;

  case 56:
#line 512 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamSpec((const Keyword*)(yystack_[3].value), (IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
  /* ParamSpec* node = reinterpret_cast<ParamSpec*> (ast_reduce_nodes(4, Type::ParamSpec)); */

  /* node->keyword_var = (const Keyword*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->id_list = (IdentList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop colon */
  /* node->spec = (TypeSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
}
#line 1738 "yacc_bison.h" // lalr1.cc:859
    break;

  case 57:
#line 524 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamSpec((IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
  /* ParamSpec* node = reinterpret_cast<ParamSpec*> (ast_reduce_nodes(3, Type::ParamSpec)); */

  /* node->id_list = (IdentList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop colon */
  /* node->spec = (TypeSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
}
#line 1753 "yacc_bison.h" // lalr1.cc:859
    break;

  case 58:
#line 537 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1761 "yacc_bison.h" // lalr1.cc:859
    break;

  case 59:
#line 543 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1769 "yacc_bison.h" // lalr1.cc:859
    break;

  case 60:
#line 548 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new SubprogramBody((ConstDecls*)(yystack_[2].value), (VarDecls*)(yystack_[1].value), (CompoundStatement*)(yystack_[0].value));
  /* SubprogramBody* node = reinterpret_cast<SubprogramBody*> (ast_reduce_nodes(3, Type::SubprogramBody)); */

  /* node->constdecls = (ConstDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->vardecls = (VarDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->compound = (CompoundStatement*)(node->children.front()); */
  /* node->children.pop_front(); */

  //ast_reduce_nodes(3, Type::Statement);
}
#line 1789 "yacc_bison.h" // lalr1.cc:859
    break;

  case 61:
#line 566 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new CompoundStatement((StatementList*)(yystack_[1].value));
  /* CompoundStatement* node = reinterpret_cast<CompoundStatement*> (ast_reduce_nodes(3, Type::CompoundStatement)); */
  /* node->children.pop_front();//pop begin */

  /* StatementList* state = (StatementList*)(node->children.front()); */
  /* node->state = state; */

  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop end */
  //ast_reduce_nodes(3, Type::Statement);
}
#line 1806 "yacc_bison.h" // lalr1.cc:859
    break;

  case 62:
#line 578 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new CompoundStatement(); }
#line 1812 "yacc_bison.h" // lalr1.cc:859
    break;

  case 63:
#line 584 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
             }
#line 1820 "yacc_bison.h" // lalr1.cc:859
    break;

  case 64:
#line 589 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
             }
#line 1828 "yacc_bison.h" // lalr1.cc:859
    break;

  case 65:
#line 595 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  ((StatementList*)(yylhs.value))->statement.push_back((Statement*)(yystack_[0].value));
  /* StatementList* node = reinterpret_cast<StatementList*> (ast_reduce_nodes(3, Type::StatementList)); */

  /* node->statement = reinterpret_cast<StatementList*>(node->children.front())->statement; */
  /* node->children.pop_front(); */

  /* node->children.pop_front();// pop semicolon */

  /* Statement* sta = (Statement*)(node->children.front()); */
  /* node->statement.push_back(sta); */
  /* node->children.pop_front(); */

  //ast_reduce_nodes(3, Type::Statement);
}
#line 1849 "yacc_bison.h" // lalr1.cc:859
    break;

  case 66:
#line 611 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new StatementList();
  ((StatementList*)(yylhs.value))->statement.push_back((Statement*)(yystack_[0].value));
  /* StatementList* node = reinterpret_cast<StatementList*> (ast_reduce_nodes(1, Type::StatementList)); */

  /* Statement* sta = (Statement*)(node->children.front()); */
  /* node->statement.push_back(sta); */
  /* node->children.pop_front(); */
  }
#line 1863 "yacc_bison.h" // lalr1.cc:859
    break;

  case 67:
#line 623 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1871 "yacc_bison.h" // lalr1.cc:859
    break;

  case 68:
#line 628 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExpVoid();  }
#line 1877 "yacc_bison.h" // lalr1.cc:859
    break;

  case 69:
#line 629 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExecStatement(new ExpAssign((Variable*)(yystack_[2].value), (Exp*)(yystack_[0].value)));}
#line 1883 "yacc_bison.h" // lalr1.cc:859
    break;

  case 70:
#line 630 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new CompoundStatement();}
#line 1889 "yacc_bison.h" // lalr1.cc:859
    break;

  case 71:
#line 631 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new CompoundStatement();}
#line 1895 "yacc_bison.h" // lalr1.cc:859
    break;

  case 72:
#line 632 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new IfElseStatement();}
#line 1901 "yacc_bison.h" // lalr1.cc:859
    break;

  case 73:
#line 633 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new IfElseStatement();}
#line 1907 "yacc_bison.h" // lalr1.cc:859
    break;

  case 74:
#line 634 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ForStatement();}
#line 1913 "yacc_bison.h" // lalr1.cc:859
    break;

  case 75:
#line 635 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new Read();}
#line 1919 "yacc_bison.h" // lalr1.cc:859
    break;

  case 76:
#line 636 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new Write();}
#line 1925 "yacc_bison.h" // lalr1.cc:859
    break;

  case 77:
#line 639 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1933 "yacc_bison.h" // lalr1.cc:859
    break;

  case 78:
#line 644 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1941 "yacc_bison.h" // lalr1.cc:859
    break;

  case 79:
#line 649 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
   }
#line 1949 "yacc_bison.h" // lalr1.cc:859
    break;

  case 80:
#line 654 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1957 "yacc_bison.h" // lalr1.cc:859
    break;

  case 81:
#line 658 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1965 "yacc_bison.h" // lalr1.cc:859
    break;

  case 82:
#line 663 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1973 "yacc_bison.h" // lalr1.cc:859
    break;

  case 83:
#line 668 "parser.y" // lalr1.cc:859
    {
   (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
        }
#line 1981 "yacc_bison.h" // lalr1.cc:859
    break;

  case 84:
#line 674 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new VariableList();
  /* VariableList* node = reinterpret_cast<VariableList*> (ast_reduce_nodes(3, Type::VariableList)); */

  /* node->params = reinterpret_cast<VariableList*>(node->children.front())->params; */
  /* node->children.pop_front(); */

  /* node->children.pop_front();// pop comma */

  /* Variable* var = (Variable*)(node->children.front()); */
  /* node->params.push_back(var); */
  /* node->children.pop_front(); */

  /* printf("variable_list\n"); */
}
#line 2001 "yacc_bison.h" // lalr1.cc:859
    break;

  case 85:
#line 689 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new VariableList();
  ((VariableList*)(yylhs.value))->params.push_back((Variable*)(yystack_[0].value));
  /* VariableList* node = reinterpret_cast<VariableList*> (ast_reduce_nodes(1, Type::VariableList)); */

  /* Variable* var = (Variable*)(node->children.front()); */
  /* node->params.push_back(var); */
  /* node->children.pop_front(); */
  }
#line 2015 "yacc_bison.h" // lalr1.cc:859
    break;

  case 86:
#line 702 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Variable((Identifier*)(yystack_[1].value), (ExpressionList*)(yystack_[0].value));
  /* Variable* node = reinterpret_cast<Variable*> (ast_reduce_nodes(2, Type::Variable)); */
  /* node->id = (Identifier*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->id_var = (ExpressionList*)(node->children.front()); */
  /* node->children.pop_front(); */
}
#line 2028 "yacc_bison.h" // lalr1.cc:859
    break;

  case 87:
#line 712 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ExpressionList(); }
#line 2034 "yacc_bison.h" // lalr1.cc:859
    break;

  case 88:
#line 713 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
  /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(3, Type::ExpressionList)); */
  /* node->children.pop_front();//pop lbracket */

  /* node->explist = reinterpret_cast<ExpressionList*>(node->children.front())->explist; */
  /* node->children.pop_front(); */

  /* node->children.pop_front();//pop rbracket */
  /* ast_reduce_nodes(3,Type::Statement); */
}
#line 2050 "yacc_bison.h" // lalr1.cc:859
    break;

  case 89:
#line 726 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2058 "yacc_bison.h" // lalr1.cc:859
    break;

  case 90:
#line 730 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2066 "yacc_bison.h" // lalr1.cc:859
    break;

  case 91:
#line 735 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpCall((const Identifier*)(yystack_[0].value), nullptr);
  //ast_reduce_nodes(1,Type::ExpCall);
}
#line 2075 "yacc_bison.h" // lalr1.cc:859
    break;

  case 92:
#line 739 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpCall((const Identifier*)(yystack_[3].value), (ExpressionList*)(yystack_[2].value));
  /* ExpCall* node = reinterpret_cast<ExpCall*> (ast_reduce_nodes(4, Type::ExpCall)); */
  /* node->fn = (Identifier*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop lparen */
  /* node->params = (ExpressionList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop rparen */
  //ast_reduce_nodes(4,Type::ExpCall);
}
#line 2091 "yacc_bison.h" // lalr1.cc:859
    break;

  case 93:
#line 755 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2099 "yacc_bison.h" // lalr1.cc:859
    break;

  case 94:
#line 759 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2107 "yacc_bison.h" // lalr1.cc:859
    break;

  case 95:
#line 763 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Ident((const Identifier *)((yystack_[0].value)));
}
#line 2115 "yacc_bison.h" // lalr1.cc:859
    break;

  case 96:
#line 768 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  ((ExpressionList*)(yylhs.value))->explist.push_back((Exp*)(yystack_[0].value));
  /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(3, Type::ExpressionList)); */

  /* node->explist = reinterpret_cast<ExpressionList*> (node->children.front())->explist; */
  /* node->children.pop_front(); */

  /* node->children.pop_front();// pop comma */

  /* Exp* exp = (Exp*)(node->children.front()); */
  /* node->explist.push_back(exp); */
  /* node->children.pop_front(); */
}
#line 2134 "yacc_bison.h" // lalr1.cc:859
    break;

  case 97:
#line 782 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpressionList();
  ((ExpressionList*)(yylhs.value))->explist.push_back((Exp*)(yystack_[0].value));
  /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(1, Type::ExpressionList)); */

  /* Exp* exp = (Exp*)(node->children.front()); */
  /* node->explist.push_back(exp); */
  /* node->children.pop_front(); */
  }
#line 2148 "yacc_bison.h" // lalr1.cc:859
    break;

  case 98:
#line 794 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2156 "yacc_bison.h" // lalr1.cc:859
    break;

  case 99:
#line 799 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpAssign((Exp*)(yystack_[2].value), (Exp*)(yystack_[0].value));
  // ast_reduce_nodes(3, Type::ExpAssign);
}
#line 2165 "yacc_bison.h" // lalr1.cc:859
    break;

  case 100:
#line 810 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2171 "yacc_bison.h" // lalr1.cc:859
    break;

  case 101:
#line 814 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value)); }
#line 2177 "yacc_bison.h" // lalr1.cc:859
    break;

  case 102:
#line 815 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2183 "yacc_bison.h" // lalr1.cc:859
    break;

  case 103:
#line 818 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value)); }
#line 2189 "yacc_bison.h" // lalr1.cc:859
    break;

  case 104:
#line 819 "parser.y" // lalr1.cc:859
    { (yylhs.value)=(yystack_[0].value); }
#line 2195 "yacc_bison.h" // lalr1.cc:859
    break;

  case 106:
#line 822 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
}
#line 2203 "yacc_bison.h" // lalr1.cc:859
    break;

  case 107:
#line 825 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[3].value);
}
#line 2211 "yacc_bison.h" // lalr1.cc:859
    break;

  case 108:
#line 828 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2219 "yacc_bison.h" // lalr1.cc:859
    break;

  case 109:
#line 831 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2227 "yacc_bison.h" // lalr1.cc:859
    break;

  case 110:
#line 834 "parser.y" // lalr1.cc:859
    {
  printf("const value\n\n");
  (yylhs.value) = (yystack_[0].value);
  }
#line 2236 "yacc_bison.h" // lalr1.cc:859
    break;

  case 111:
#line 839 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2244 "yacc_bison.h" // lalr1.cc:859
    break;

  case 112:
#line 843 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2252 "yacc_bison.h" // lalr1.cc:859
    break;

  case 113:
#line 847 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2260 "yacc_bison.h" // lalr1.cc:859
    break;

  case 114:
#line 850 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2268 "yacc_bison.h" // lalr1.cc:859
    break;

  case 115:
#line 853 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2276 "yacc_bison.h" // lalr1.cc:859
    break;

  case 116:
#line 858 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2284 "yacc_bison.h" // lalr1.cc:859
    break;

  case 117:
#line 861 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2292 "yacc_bison.h" // lalr1.cc:859
    break;

  case 118:
#line 864 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2300 "yacc_bison.h" // lalr1.cc:859
    break;

  case 119:
#line 867 "parser.y" // lalr1.cc:859
    {
  printf("logicand\n\n");
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2309 "yacc_bison.h" // lalr1.cc:859
    break;

  case 120:
#line 872 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2317 "yacc_bison.h" // lalr1.cc:859
    break;

  case 121:
#line 875 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2325 "yacc_bison.h" // lalr1.cc:859
    break;

  case 122:
#line 878 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2333 "yacc_bison.h" // lalr1.cc:859
    break;

  case 123:
#line 881 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2341 "yacc_bison.h" // lalr1.cc:859
    break;

  case 124:
#line 884 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2349 "yacc_bison.h" // lalr1.cc:859
    break;

  case 125:
#line 887 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2357 "yacc_bison.h" // lalr1.cc:859
    break;


#line 2361 "yacc_bison.h" // lalr1.cc:859
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

  const signed char parser::yytable_ninf_ = -88;

  const short int
  parser::yypact_[] =
  {
      13,  -111,    26,   -44,    24,  -111,  -111,    32,  -111,    -1,
    -111,    -2,    48,    24,  -111,    24,  -111,  -111,  -111,  -111,
      24,   -44,    21,   -11,  -111,   111,   -10,   -44,    24,  -111,
      69,  -111,  -111,  -111,    24,  -111,  -111,  -111,   -44,   -44,
      24,    24,  -111,   134,  -111,   155,    24,    21,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,    60,    60,
    -111,  -111,    32,    -1,    -1,  -111,  -111,    -1,    -1,  -111,
      17,  -111,    24,   133,    25,  -111,    28,  -111,  -111,  -111,
    -111,  -111,  -111,    31,  -111,  -111,  -111,  -111,   -10,    69,
    -111,  -111,    48,  -111,  -111,    20,    34,    24,   133,  -111,
    -111,   134,    25,  -111,    87,  -111,  -111,     5,    74,   152,
      94,  -111,   133,   133,  -111,   133,  -111,  -111,   133,   133,
      60,   155,  -111,    88,   -10,   -14,  -111,    24,   163,   -11,
    -111,    31,   -11,  -111,  -111,  -111,   133,   133,  -111,   134,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,   133,
     133,  -111,  -111,  -111,  -111,   133,  -111,  -111,  -111,    16,
     -11,    63,    16,  -111,  -111,   163,    20,  -111,   -10,  -111,
    -111,    24,  -111,   133,    79,   -11,    82,    94,    85,  -111,
    -111,  -111,  -111,  -111,    60,    80,    60,  -111,  -111,   163,
    -111,  -111,  -111,   133,  -111,  -111,   134,  -111,  -111,   163,
      63,  -111,    83,  -111,  -111,    60,  -111,   134,  -111,  -111
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     6,     0,     0,     0,     1,    67,    11,    95,     5,
      12,     0,    26,     0,    93,     0,     3,     2,    58,    46,
       0,     0,     0,     0,     9,     0,     0,     0,    10,    15,
       0,    94,    98,     4,     0,    50,    51,    63,     0,     0,
       0,     0,     7,    68,    59,     0,    27,     0,    23,    22,
      21,    39,    24,    25,    14,    20,    18,    19,     0,     0,
       8,    45,    11,    52,    52,    81,    77,     0,     0,    71,
       0,    66,     0,   105,     0,    70,    91,    32,    38,    40,
      41,    37,    29,     0,    30,    34,    35,    36,     0,     0,
      16,    17,    26,    47,    48,     0,     0,     0,   105,    64,
      61,    68,     0,   111,   112,   110,   106,    87,     0,   100,
     102,   104,   105,   105,    80,   105,    89,    86,   105,   105,
       0,     0,    13,     0,     0,     0,    55,     0,     0,     0,
      85,    87,     0,    97,    62,    65,   105,   105,    82,    68,
     121,   124,   125,   122,   120,   123,   113,   114,   115,   105,
     105,   116,   117,   118,   119,   105,   108,   109,    69,     0,
       0,     0,     0,    28,    60,     0,     0,    53,     0,    49,
      75,     0,    76,   105,     0,     0,    73,   101,    99,   103,
      90,    88,    92,    44,     0,     0,     0,    57,    54,     0,
      84,    96,    78,   105,   107,    83,    68,    43,    33,     0,
       0,    56,     0,    72,    31,     0,    79,    68,    42,    74
  };

  const signed char
  parser::yypgoto_[] =
  {
    -111,  -111,  -111,  -111,  -111,  -111,    -8,    51,  -111,  -111,
      68,   -20,  -111,   -55,   -40,  -111,  -111,    30,  -111,     3,
    -111,  -111,  -110,  -111,  -111,  -111,  -111,   -80,  -111,  -111,
    -111,  -111,  -111,    84,  -111,   -13,   -76,   -73,  -111,   -19,
    -111,  -111,  -111,  -111,    -7,   -93,  -111,  -111,  -111,    52,
    -111,  -111,  -111,  -111,   -41,  -111,    81,    -5,  -111,     4,
     -75,    -4,   -97,   -23,   -72,    15,    14,   -85,  -111,  -111,
    -111,  -111,  -111
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     2,    17,     3,     4,    11,   124,    12,    13,    21,
      30,   105,    55,    56,    57,    58,    59,    19,    27,    82,
      83,   199,    84,    85,    86,    87,   162,   184,    25,    38,
      39,    40,    41,    94,   125,   126,    20,    45,    93,    69,
     134,    43,   100,    70,     7,    71,    72,   193,   207,   115,
      73,   139,   196,   129,   106,   117,   118,   181,    75,    95,
      33,   107,   132,    34,   133,   109,   110,   111,   112,   113,
     149,   155,   150
  };

  const short int
  parser::yytable_[] =
  {
       9,   108,    74,    90,    91,    81,    42,    23,   135,    22,
      54,    24,    26,    15,    28,   121,    24,     6,   169,   127,
      46,   159,   160,   128,    47,     1,     5,   156,   157,     8,
      60,    61,    62,     8,    18,    99,    63,    64,    88,    76,
     175,    31,    24,   158,    31,    10,   176,     6,    32,    32,
     167,   165,    44,    14,   170,   187,   130,   172,    16,    14,
      74,   116,    18,   101,   174,   161,    29,    49,   102,   122,
     179,    97,    98,   180,    48,    32,    49,    50,     6,   201,
     119,    81,    14,   114,   116,   182,   -87,   116,    81,   204,
     127,    24,    51,   131,   -25,   189,    44,    76,    74,   138,
     194,   191,   183,   203,   164,    37,   171,   192,   195,   173,
     198,   137,   206,    92,   209,    89,    52,    53,   166,   168,
     205,   202,   123,    24,   163,    81,    35,    36,    37,   197,
     190,   200,   146,   147,   148,    76,   173,   173,    48,   186,
      49,    50,     8,     8,   151,   152,   153,   154,    96,    81,
     208,    37,   173,   188,   136,    74,    51,   185,    65,    81,
      48,    66,    24,   177,   120,   178,    74,   131,    48,     0,
      67,    68,     0,   103,    77,    78,    79,    80,    51,     0,
      52,   104,     0,    78,    79,    80,    51,     0,     0,     0,
       0,     0,    76,   140,   141,   142,   143,   144,   145,   146,
     147,   148,     0,    76
  };

  const short int
  parser::yycheck_[] =
  {
       4,    73,    43,    58,    59,    45,    25,    15,   101,    13,
      30,    15,    20,     9,    21,    88,    20,    61,   128,    95,
      27,   118,   119,    96,    28,    12,     0,   112,   113,     9,
      34,    38,    39,     9,    14,    18,    40,    41,    46,    43,
     137,    55,    46,   115,    55,    13,   139,    61,    59,    59,
     125,   124,    62,    54,   129,   165,    97,   132,    60,    54,
     101,    56,    14,    70,   136,   120,    45,     7,    72,    89,
     155,    67,    68,    57,     5,    59,     7,     8,    61,   189,
      76,   121,    54,    58,    56,   160,    58,    56,   128,   199,
     166,    95,    23,    97,     7,   168,    62,   101,   139,    25,
     175,   173,    39,   196,   123,    17,   129,    28,    26,   132,
      30,   107,    29,    62,   207,    47,    47,    48,   125,   127,
     200,   193,    92,   127,   121,   165,    15,    16,    17,   184,
     171,   186,    47,    48,    49,   139,   159,   160,     5,   162,
       7,     8,     9,     9,    50,    51,    52,    53,    64,   189,
     205,    17,   175,   166,   102,   196,    23,   162,    24,   199,
       5,    27,   166,   149,    83,   150,   207,   171,     5,    -1,
      36,    37,    -1,    40,    19,    20,    21,    22,    23,    -1,
      47,    48,    -1,    20,    21,    22,    23,    -1,    -1,    -1,
      -1,    -1,   196,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    -1,   207
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    12,    64,    66,    67,     0,    61,   107,     9,   124,
      13,    68,    70,    71,    54,   122,    60,    65,    14,    80,
      99,    72,   124,    69,   124,    91,    69,    81,   107,    45,
      73,    55,    59,   123,   126,    15,    16,    17,    92,    93,
      94,    95,   102,   104,    62,   100,   107,   124,     5,     7,
       8,    23,    47,    48,    74,    75,    76,    77,    78,    79,
     124,   107,   107,   124,   124,    24,    27,    36,    37,   102,
     106,   108,   109,   113,   117,   121,   124,    19,    20,    21,
      22,    77,    82,    83,    85,    86,    87,    88,    69,    73,
      76,    76,    70,   101,    96,   122,    96,   122,   122,    18,
     105,   107,   124,    40,    48,    74,   117,   124,   127,   128,
     129,   130,   131,   132,    58,   112,    56,   118,   119,   122,
     119,   100,    74,    80,    69,    97,    98,    99,   100,   116,
     117,   124,   125,   127,   103,   108,   112,   122,    25,   114,
      41,    42,    43,    44,    45,    46,    47,    48,    49,   133,
     135,    50,    51,    52,    53,   134,   130,   130,   127,   125,
     125,    76,    89,    82,   102,   100,   107,   123,    69,    85,
     123,   126,   123,   126,   127,   125,   108,   129,   128,   130,
      57,   120,   123,    39,    90,   120,   126,    85,    98,   100,
     117,   127,    28,   110,   123,    26,   115,    76,    30,    84,
      76,    85,   127,   108,    85,    90,    29,   111,    76,   108
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    63,    64,    65,    66,    66,    67,    68,    69,    69,
      70,    70,    71,    72,    72,    73,    74,    74,    74,    74,
      74,    75,    76,    77,    78,    79,    80,    80,    81,    81,
      82,    82,    83,    84,    85,    85,    85,    85,    86,    77,
      87,    88,    89,    89,    90,    91,    91,    92,    93,    93,
      94,    95,    96,    96,    97,    97,    98,    98,    99,   100,
     101,   103,   102,   104,   105,   106,   106,   107,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   116,   117,   118,   118,   119,
     120,   121,   121,   122,   123,   124,   125,   125,   126,   127,
     127,   128,   128,   129,   129,   130,   130,   130,   130,   130,
     130,   131,   132,   133,   133,   133,   134,   134,   134,   134,
     135,   135,   135,   135,   135,   135
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     4,     1,     5,     2,     1,     4,     3,     1,
       3,     0,     1,     5,     3,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     5,     3,
       1,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     3,     1,     3,     0,     3,     3,     5,
       1,     1,     0,     3,     3,     1,     4,     3,     1,     1,
       3,     0,     4,     1,     1,     3,     1,     1,     0,     3,
       1,     1,     6,     4,     8,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     2,     0,     3,     1,
       1,     1,     4,     1,     1,     1,     3,     1,     1,     3,
       1,     3,     1,     3,     1,     0,     1,     4,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "KEYWORD", "STR", "CHAR", "REAL", "INT",
  "BOOL", "IDENT", "NULLPTR", "LENGTH", "KEYWORD_PROGRAM", "KEYWORD_CONST",
  "KEYWORD_VAR", "KEYWORD_PROCEDURE", "KEYWORD_FUNCTION", "KEYWORD_BEGIN",
  "KEYWORD_END", "KEYWORD_ARRAY", "KEYWORD_INTEGER", "KEYWORD_REAL",
  "KEYWORD_BOOLEAN", "KEYWORD_CHAR", "KEYWORD_IF", "KEYWORD_THEN",
  "KEYWORD_ELSE", "KEYWORD_FOR", "KEYWORD_TO", "KEYWORD_DO", "KEYWORD_OF",
  "KEYWORD_DIV", "KEYWORD_MOD", "KEYWORD_AND", "KEYWORD_OR", "KEYWORD_NOT",
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
  "colon", "subprogram_body", "compound_statement", "@1", "begin", "end",
  "statement_list", "semicolon", "statement", "for", "to", "do", "assign",
  "if", "then", "else", "variable_list", "variable", "id_varpart",
  "lbracket", "rbracket", "procedure_call", "lparen", "rparen", "id",
  "expression_list", "comma", "expression", "simple_expression", "term",
  "factor", "not", "unimus", "addop", "mulop", "relop", YY_NULLPTR
  };


  const unsigned short int
  parser::yyrline_[] =
  {
       0,    82,    82,    99,   105,   117,   129,   134,   153,   164,
     176,   184,   189,   195,   215,   239,   245,   246,   247,   248,
     249,   252,   254,   259,   264,   269,   274,   275,   287,   308,
     330,   333,   339,   344,   350,   351,   352,   353,   356,   361,
     366,   371,   377,   382,   388,   393,   408,   413,   426,   442,
     460,   465,   470,   471,   486,   498,   512,   524,   537,   543,
     548,   566,   566,   584,   589,   595,   611,   623,   628,   629,
     630,   631,   632,   633,   634,   635,   636,   639,   644,   649,
     654,   658,   663,   668,   674,   689,   702,   712,   713,   726,
     730,   735,   739,   755,   759,   763,   768,   782,   794,   799,
     810,   814,   815,   818,   819,   821,   822,   825,   828,   831,
     834,   839,   843,   847,   850,   853,   858,   861,   864,   867,
     872,   875,   878,   881,   884,   887
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
      11,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,    39,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
      42,    43,    44,    45,    46,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    47,    48,    49,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      50,    51,    52,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    54,    55,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    56,    57,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    59,
      60,    61,    62,     1,     2
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
#line 2886 "yacc_bison.h" // lalr1.cc:1167
#line 890 "parser.y" // lalr1.cc:1168

