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
        MARKER_LOGICAND = 513,
        MARKER_LOGICOR = 514,
        MARKER_LOGICNOT = 515,
        MARKER_NEQ = 529,
        MARKER_LE = 530,
        MARKER_GE = 531,
        MARKER_LT = 532,
        MARKER_EQ = 533,
        MARKER_GT = 534,
        MARKER_ADD = 544,
        MARKER_SUB = 545,
        MARKER_MUL = 560,
        MARKER_DIV = 561,
        MARKER_MOD = 562,
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
  static const signed char yypact_[];

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
      yylast_ = 198,     ///< Last index in yytable_.
      yynnts_ = 72,  ///< Number of nonterminal symbols.
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
#line 98 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Program((ProgramHead*)(yystack_[3].value), (ProgramBody*)(yystack_[1].value));
  access_ast((yylhs.value));
  /* Program *node = reinterpret_cast<Program*> (ast_reduce_nodes(4, Type::Program)); */
  /* node->programHead = (ProgramHead*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop semicolon */
  /* node->programBody = (ProgramBody*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop dot */
 }
#line 1136 "yacc_bison.h" // lalr1.cc:859
    break;

  case 3:
#line 114 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1145 "yacc_bison.h" // lalr1.cc:859
    break;

  case 4:
#line 121 "parser.y" // lalr1.cc:859
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
#line 133 "parser.y" // lalr1.cc:859
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
#line 145 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1184 "yacc_bison.h" // lalr1.cc:859
    break;

  case 7:
#line 151 "parser.y" // lalr1.cc:859
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
#line 1205 "yacc_bison.h" // lalr1.cc:859
    break;

  case 8:
#line 170 "parser.y" // lalr1.cc:859
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
#line 1221 "yacc_bison.h" // lalr1.cc:859
    break;

  case 9:
#line 181 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new IdentList();
  ((IdentList*)(yylhs.value))->idents.push_back((Identifier*)(yystack_[0].value));
    /* IdentList* node = reinterpret_cast<IdentList*> (ast_reduce_nodes(1, Type::IdentList)); */
    /* Identifier* id = (Identifier*)(node->children.front()); */
    /* node->idents.push_back(id); */
    /* node->children.pop_front(); */
  }
#line 1234 "yacc_bison.h" // lalr1.cc:859
    break;

  case 10:
#line 193 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = (yystack_[1].value);
    /* ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(3, Type::ConstDecls)); */
    /* node->children.pop_front();// pop const */
    /* node->decls = reinterpret_cast<ConstDecls*>(node->children.front())->decls; */
    /* node->children.pop_front(); */
    /* node->children.pop_front();// pop semicolon */
  }
#line 1247 "yacc_bison.h" // lalr1.cc:859
    break;

  case 11:
#line 201 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ConstDecls(); }
#line 1253 "yacc_bison.h" // lalr1.cc:859
    break;

  case 12:
#line 206 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1262 "yacc_bison.h" // lalr1.cc:859
    break;

  case 13:
#line 213 "parser.y" // lalr1.cc:859
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
#line 1287 "yacc_bison.h" // lalr1.cc:859
    break;

  case 14:
#line 233 "parser.y" // lalr1.cc:859
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
#line 1313 "yacc_bison.h" // lalr1.cc:859
    break;

  case 15:
#line 257 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 1322 "yacc_bison.h" // lalr1.cc:859
    break;

  case 16:
#line 263 "parser.y" // lalr1.cc:859
    {ast_reduce_nodes(2, Type::Statement);}
#line 1328 "yacc_bison.h" // lalr1.cc:859
    break;

  case 17:
#line 264 "parser.y" // lalr1.cc:859
    {ast_reduce_nodes(2, Type::Statement);}
#line 1334 "yacc_bison.h" // lalr1.cc:859
    break;

  case 18:
#line 265 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1340 "yacc_bison.h" // lalr1.cc:859
    break;

  case 19:
#line 266 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1346 "yacc_bison.h" // lalr1.cc:859
    break;

  case 20:
#line 270 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantInteger(((const ConstantInteger*)((yystack_[0].value))));
  // access_ast($$);
}
#line 1355 "yacc_bison.h" // lalr1.cc:859
    break;

  case 21:
#line 276 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantChar(((const ConstantChar*)((yystack_[0].value))));
  // access_ast($$);
}
#line 1364 "yacc_bison.h" // lalr1.cc:859
    break;

  case 22:
#line 282 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1373 "yacc_bison.h" // lalr1.cc:859
    break;

  case 23:
#line 288 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1382 "yacc_bison.h" // lalr1.cc:859
    break;

  case 24:
#line 294 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ExpVoid();  /* access_ast($$); */ }
#line 1388 "yacc_bison.h" // lalr1.cc:859
    break;

  case 25:
#line 295 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
    /* VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(3, Type::VarDecls)); */
    /* node->children.pop_front();// pop var */
    /* node->decls = reinterpret_cast<VarDecls*>(node->children.front())->decls; */
    /* node->children.pop_front(); */
    /* node->children.pop_front();// pop semicolon */
}
#line 1401 "yacc_bison.h" // lalr1.cc:859
    break;

  case 26:
#line 307 "parser.y" // lalr1.cc:859
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
#line 1427 "yacc_bison.h" // lalr1.cc:859
    break;

  case 27:
#line 328 "parser.y" // lalr1.cc:859
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
#line 1450 "yacc_bison.h" // lalr1.cc:859
    break;

  case 28:
#line 350 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
}
#line 1458 "yacc_bison.h" // lalr1.cc:859
    break;

  case 29:
#line 353 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[3].value);
  ((ArrayTypeSpec*)(yylhs.value))->keyword = ((BasicTypeSpec*)(yystack_[0].value))->keyword;
}
#line 1467 "yacc_bison.h" // lalr1.cc:859
    break;

  case 30:
#line 359 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1476 "yacc_bison.h" // lalr1.cc:859
    break;

  case 31:
#line 365 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1485 "yacc_bison.h" // lalr1.cc:859
    break;

  case 32:
#line 372 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1491 "yacc_bison.h" // lalr1.cc:859
    break;

  case 33:
#line 373 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1497 "yacc_bison.h" // lalr1.cc:859
    break;

  case 34:
#line 374 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1503 "yacc_bison.h" // lalr1.cc:859
    break;

  case 35:
#line 375 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1509 "yacc_bison.h" // lalr1.cc:859
    break;

  case 36:
#line 378 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1518 "yacc_bison.h" // lalr1.cc:859
    break;

  case 37:
#line 384 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1527 "yacc_bison.h" // lalr1.cc:859
    break;

  case 38:
#line 390 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1536 "yacc_bison.h" // lalr1.cc:859
    break;

  case 39:
#line 396 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1545 "yacc_bison.h" // lalr1.cc:859
    break;

  case 40:
#line 403 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[4].value);
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)(yystack_[2].value), (int64_t)(yystack_[0].value)));
  //ast_reduce_nodes(5, Type::ArrayTypeSpec);
}
#line 1555 "yacc_bison.h" // lalr1.cc:859
    break;

  case 41:
#line 408 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ArrayTypeSpec();
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)(yystack_[2].value), (int64_t)(yystack_[0].value)));
  //ast_reduce_nodes(3, Type::ArrayTypeSpec);
}
#line 1565 "yacc_bison.h" // lalr1.cc:859
    break;

  case 42:
#line 414 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1574 "yacc_bison.h" // lalr1.cc:859
    break;

  case 43:
#line 419 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new SubprogramDecls();  access_ast((yylhs.value)); }
#line 1580 "yacc_bison.h" // lalr1.cc:859
    break;

  case 44:
#line 420 "parser.y" // lalr1.cc:859
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
#line 1600 "yacc_bison.h" // lalr1.cc:859
    break;

  case 45:
#line 439 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new Subprogram((SubprogramHead*)(yystack_[2].value), (SubprogramBody*)(yystack_[0].value));
    /* Subprogram* node = reinterpret_cast<Subprogram*> (ast_reduce_nodes(3, Type::Subprogram)); */
    /* node->subhead = (SubprogramHead*)(node->children.front()); */
    /* node->children.pop_front(); */
    /* node->children.pop_front();// pop semicolon */
    /* node->subbody = (SubprogramBody*)(node->children.front()); */
    /* node->children.pop_front(); */
}
#line 1614 "yacc_bison.h" // lalr1.cc:859
    break;

  case 46:
#line 452 "parser.y" // lalr1.cc:859
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
#line 1635 "yacc_bison.h" // lalr1.cc:859
    break;

  case 47:
#line 468 "parser.y" // lalr1.cc:859
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
#line 1656 "yacc_bison.h" // lalr1.cc:859
    break;

  case 48:
#line 486 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1665 "yacc_bison.h" // lalr1.cc:859
    break;

  case 49:
#line 492 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1674 "yacc_bison.h" // lalr1.cc:859
    break;

  case 50:
#line 498 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ParamList();  /* access_ast($$); */  }
#line 1680 "yacc_bison.h" // lalr1.cc:859
    break;

  case 51:
#line 499 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(3, Type::ParamList)); */
  /* node->children.pop_front();//pop lparen */
  /* node->params = reinterpret_cast<ParamList*>(node->children.front())->params; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop rparen */
  //ast_reduce_nodes(3, Type::ParamList);
}
#line 1694 "yacc_bison.h" // lalr1.cc:859
    break;

  case 52:
#line 514 "parser.y" // lalr1.cc:859
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
#line 1711 "yacc_bison.h" // lalr1.cc:859
    break;

  case 53:
#line 526 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamList();
  ((ParamList*)(yylhs.value))->params.push_back((ParamSpec*)(yystack_[0].value));
    /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(1, Type::ParamList)); */
    /* ParamSpec* param = (ParamSpec*)(node->children.front()); */
    /* node->children.pop_front(); */
    /* node->params.push_back(param); */
    //$$ = $1;
}
#line 1725 "yacc_bison.h" // lalr1.cc:859
    break;

  case 54:
#line 540 "parser.y" // lalr1.cc:859
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
#line 1742 "yacc_bison.h" // lalr1.cc:859
    break;

  case 55:
#line 552 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamSpec((IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
    /* ParamSpec* node = reinterpret_cast<ParamSpec*> (ast_reduce_nodes(3, Type::ParamSpec)); */

    /* node->id_list = (IdentList*)(node->children.front()); */
    /* node->children.pop_front(); */
    /* node->children.pop_front();// pop colon */
    /* node->spec = (TypeSpec*)(node->children.front()); */
    /* node->children.pop_front(); */
}
#line 1757 "yacc_bison.h" // lalr1.cc:859
    break;

  case 56:
#line 565 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1766 "yacc_bison.h" // lalr1.cc:859
    break;

  case 57:
#line 572 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1775 "yacc_bison.h" // lalr1.cc:859
    break;

  case 58:
#line 578 "parser.y" // lalr1.cc:859
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
#line 1795 "yacc_bison.h" // lalr1.cc:859
    break;

  case 59:
#line 595 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new CompoundStatement();  access_ast((yylhs.value));  }
#line 1801 "yacc_bison.h" // lalr1.cc:859
    break;

  case 60:
#line 596 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new CompoundStatement((StatementList*)(yystack_[2].value));
    /* CompoundStatement* node = reinterpret_cast<CompoundStatement*> (ast_reduce_nodes(3, Type::CompoundStatement)); */
    /* node->children.pop_front();//pop begin */

    /* StatementList* state = (StatementList*)(node->children.front()); */
    /* node->state = state; */

    /* node->children.pop_front(); */
    /* node->children.pop_front();//pop end */
    //ast_reduce_nodes(3, Type::Statement);
}
#line 1818 "yacc_bison.h" // lalr1.cc:859
    break;

  case 61:
#line 613 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1827 "yacc_bison.h" // lalr1.cc:859
    break;

  case 62:
#line 619 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1836 "yacc_bison.h" // lalr1.cc:859
    break;

  case 63:
#line 626 "parser.y" // lalr1.cc:859
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
#line 1857 "yacc_bison.h" // lalr1.cc:859
    break;

  case 64:
#line 642 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new StatementList();
  ((StatementList*)(yylhs.value))->statement.push_back((Statement*)(yystack_[0].value));
    /* StatementList* node = reinterpret_cast<StatementList*> (ast_reduce_nodes(1, Type::StatementList)); */

    /* Statement* sta = (Statement*)(node->children.front()); */
    /* node->statement.push_back(sta); */
    /* node->children.pop_front(); */
}
#line 1871 "yacc_bison.h" // lalr1.cc:859
    break;

  case 65:
#line 654 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1880 "yacc_bison.h" // lalr1.cc:859
    break;

  case 66:
#line 659 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExpVoid();  }
#line 1886 "yacc_bison.h" // lalr1.cc:859
    break;

  case 67:
#line 660 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExecStatement(new ExpAssign((Variable*)(yystack_[2].value), (Exp*)(yystack_[0].value)));}
#line 1892 "yacc_bison.h" // lalr1.cc:859
    break;

  case 68:
#line 661 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new CompoundStatement();}
#line 1898 "yacc_bison.h" // lalr1.cc:859
    break;

  case 69:
#line 662 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new CompoundStatement();}
#line 1904 "yacc_bison.h" // lalr1.cc:859
    break;

  case 70:
#line 663 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new IfElseStatement();}
#line 1910 "yacc_bison.h" // lalr1.cc:859
    break;

  case 71:
#line 664 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new IfElseStatement();}
#line 1916 "yacc_bison.h" // lalr1.cc:859
    break;

  case 72:
#line 665 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ForStatement();}
#line 1922 "yacc_bison.h" // lalr1.cc:859
    break;

  case 73:
#line 666 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new Read();}
#line 1928 "yacc_bison.h" // lalr1.cc:859
    break;

  case 74:
#line 667 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new Write();}
#line 1934 "yacc_bison.h" // lalr1.cc:859
    break;

  case 75:
#line 670 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1943 "yacc_bison.h" // lalr1.cc:859
    break;

  case 76:
#line 676 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1952 "yacc_bison.h" // lalr1.cc:859
    break;

  case 77:
#line 682 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1961 "yacc_bison.h" // lalr1.cc:859
    break;

  case 78:
#line 688 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1970 "yacc_bison.h" // lalr1.cc:859
    break;

  case 79:
#line 693 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1979 "yacc_bison.h" // lalr1.cc:859
    break;

  case 80:
#line 699 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1988 "yacc_bison.h" // lalr1.cc:859
    break;

  case 81:
#line 705 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
    // access_ast($$);
}
#line 1997 "yacc_bison.h" // lalr1.cc:859
    break;

  case 82:
#line 712 "parser.y" // lalr1.cc:859
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
#line 2017 "yacc_bison.h" // lalr1.cc:859
    break;

  case 83:
#line 727 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new VariableList();
  ((VariableList*)(yylhs.value))->params.push_back((Variable*)(yystack_[0].value));
    /* VariableList* node = reinterpret_cast<VariableList*> (ast_reduce_nodes(1, Type::VariableList)); */

    /* Variable* var = (Variable*)(node->children.front()); */
    /* node->params.push_back(var); */
    /* node->children.pop_front(); */
}
#line 2031 "yacc_bison.h" // lalr1.cc:859
    break;

  case 84:
#line 740 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new Variable((Identifier*)(yystack_[1].value), (ExpressionList*)(yystack_[0].value));
    /* Variable* node = reinterpret_cast<Variable*> (ast_reduce_nodes(2, Type::Variable)); */
    /* node->id = (Identifier*)(node->children.front()); */
    /* node->children.pop_front(); */
    /* node->id_var = (ExpressionList*)(node->children.front()); */
    /* node->children.pop_front(); */
}
#line 2044 "yacc_bison.h" // lalr1.cc:859
    break;

  case 85:
#line 750 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ExpressionList(); }
#line 2050 "yacc_bison.h" // lalr1.cc:859
    break;

  case 86:
#line 751 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
    /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(3, Type::ExpressionList)); */
    /* node->children.pop_front();//pop lbracket */

    /* node->explist = reinterpret_cast<ExpressionList*>(node->children.front())->explist; */
    /* node->children.pop_front(); */

    /* node->children.pop_front();//pop rbracket */
    /* ast_reduce_nodes(3,Type::Statement); */
  }
#line 2066 "yacc_bison.h" // lalr1.cc:859
    break;

  case 87:
#line 764 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2075 "yacc_bison.h" // lalr1.cc:859
    break;

  case 88:
#line 769 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2084 "yacc_bison.h" // lalr1.cc:859
    break;

  case 89:
#line 775 "parser.y" // lalr1.cc:859
    {
    ExpCall* node = reinterpret_cast<ExpCall*> (ast_reduce_nodes(1, Type::ExpCall));
    node->fn = (Identifier*)(node->children.front());
    node->children.pop_front();
    //ast_reduce_nodes(1,Type::ExpCall);
  }
#line 2095 "yacc_bison.h" // lalr1.cc:859
    break;

  case 90:
#line 781 "parser.y" // lalr1.cc:859
    {
    ExpCall* node = reinterpret_cast<ExpCall*> (ast_reduce_nodes(4, Type::ExpCall));
    node->fn = (Identifier*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();//pop lparen
    node->params = (ExpressionList*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();//pop rparen
    //ast_reduce_nodes(4,Type::ExpCall);
  }
#line 2110 "yacc_bison.h" // lalr1.cc:859
    break;

  case 91:
#line 796 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2119 "yacc_bison.h" // lalr1.cc:859
    break;

  case 92:
#line 801 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2128 "yacc_bison.h" // lalr1.cc:859
    break;

  case 93:
#line 806 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new Ident((const Identifier *)((yystack_[0].value)));
    // access_ast($$);
}
#line 2137 "yacc_bison.h" // lalr1.cc:859
    break;

  case 94:
#line 812 "parser.y" // lalr1.cc:859
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
#line 2156 "yacc_bison.h" // lalr1.cc:859
    break;

  case 95:
#line 826 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpressionList();
  ((ExpressionList*)(yylhs.value))->explist.push_back((Exp*)(yystack_[0].value));
    /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(1, Type::ExpressionList)); */

    /* Exp* exp = (Exp*)(node->children.front()); */
    /* node->explist.push_back(exp); */
    /* node->children.pop_front(); */
}
#line 2170 "yacc_bison.h" // lalr1.cc:859
    break;

  case 96:
#line 838 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
}
#line 2179 "yacc_bison.h" // lalr1.cc:859
    break;

  case 97:
#line 844 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpAssign((Exp*)(yystack_[2].value), (Exp*)(yystack_[0].value));
  // ast_reduce_nodes(3, Type::ExpAssign);
}
#line 2188 "yacc_bison.h" // lalr1.cc:859
    break;

  case 98:
#line 855 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2194 "yacc_bison.h" // lalr1.cc:859
    break;

  case 99:
#line 859 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value)); }
#line 2200 "yacc_bison.h" // lalr1.cc:859
    break;

  case 100:
#line 860 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2206 "yacc_bison.h" // lalr1.cc:859
    break;

  case 101:
#line 863 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value)); }
#line 2212 "yacc_bison.h" // lalr1.cc:859
    break;

  case 102:
#line 864 "parser.y" // lalr1.cc:859
    { (yylhs.value)=(yystack_[0].value); }
#line 2218 "yacc_bison.h" // lalr1.cc:859
    break;

  case 103:
#line 867 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantInteger(((const ConstantInteger*)((yystack_[0].value))));
  // access_ast($$);
}
#line 2227 "yacc_bison.h" // lalr1.cc:859
    break;

  case 104:
#line 871 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Ident(((const Identifier*)((yystack_[0].value))));
  // access_ast($$);
}
#line 2236 "yacc_bison.h" // lalr1.cc:859
    break;

  case 105:
#line 876 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2245 "yacc_bison.h" // lalr1.cc:859
    break;

  case 106:
#line 880 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2254 "yacc_bison.h" // lalr1.cc:859
    break;

  case 107:
#line 884 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2263 "yacc_bison.h" // lalr1.cc:859
    break;

  case 108:
#line 890 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2272 "yacc_bison.h" // lalr1.cc:859
    break;

  case 109:
#line 894 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
  }
#line 2281 "yacc_bison.h" // lalr1.cc:859
    break;

  case 110:
#line 898 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
  }
#line 2290 "yacc_bison.h" // lalr1.cc:859
    break;

  case 111:
#line 902 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
  }
#line 2299 "yacc_bison.h" // lalr1.cc:859
    break;

  case 112:
#line 907 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2308 "yacc_bison.h" // lalr1.cc:859
    break;

  case 113:
#line 911 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2317 "yacc_bison.h" // lalr1.cc:859
    break;

  case 114:
#line 915 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2326 "yacc_bison.h" // lalr1.cc:859
    break;

  case 115:
#line 919 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2335 "yacc_bison.h" // lalr1.cc:859
    break;

  case 116:
#line 923 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2344 "yacc_bison.h" // lalr1.cc:859
    break;

  case 117:
#line 927 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2353 "yacc_bison.h" // lalr1.cc:859
    break;


#line 2357 "yacc_bison.h" // lalr1.cc:859
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


  const signed char parser::yypact_ninf_ = -108;

  const signed char parser::yytable_ninf_ = -86;

  const signed char
  parser::yypact_[] =
  {
       7,  -108,    45,     9,    66,  -108,  -108,    65,  -108,    50,
    -108,    22,    93,    66,  -108,    66,  -108,  -108,  -108,  -108,
      66,     9,    69,    10,  -108,    95,   -11,     9,    66,  -108,
      27,  -108,  -108,  -108,    66,  -108,  -108,     9,     9,    66,
      66,  -108,   100,  -108,   109,    66,    69,  -108,  -108,  -108,
    -108,  -108,  -108,  -108,  -108,   113,   113,  -108,  -108,    65,
      50,    50,  -108,    86,  -108,  -108,  -108,  -108,  -108,  -108,
      70,  -108,  -108,  -108,  -108,   -11,    27,  -108,  -108,    93,
    -108,  -108,    19,    71,  -108,    50,    50,  -108,    -5,  -108,
      66,    76,  -108,     8,  -108,   113,   109,  -108,  -108,   -11,
     -12,  -108,    66,   116,    66,    31,   103,  -108,  -108,    86,
      76,  -108,    31,  -108,    31,    31,   101,    28,  -108,  -108,
     116,    19,  -108,   -11,  -108,    10,  -108,    70,  -108,  -108,
      10,  -108,   105,    21,  -108,  -108,    31,  -108,    31,  -108,
      28,    10,  -108,   113,  -108,   111,   113,  -108,  -108,   116,
    -108,    66,  -108,    31,  -108,  -108,  -108,  -108,  -108,  -108,
    -108,  -108,  -108,    31,    31,  -108,  -108,  -108,  -108,    31,
     117,   115,  -108,  -108,  -108,  -108,   116,   101,  -108,  -108,
    -108,    21,   -23,  -108,  -108,    82,  -108,    31,  -108,   113,
     118,   127,  -108,  -108,    88,  -108,    86,  -108,  -108,   103,
      31,   117,    86,  -108
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     6,     0,     0,     0,     1,    65,    11,    93,     5,
      12,     0,    24,     0,    91,     0,     3,     2,    56,    43,
       0,     0,     0,     0,     9,    59,     0,     0,    10,    15,
       0,    92,    96,     4,     0,    48,    49,     0,     0,     0,
       0,     7,     0,    57,     0,    25,     0,    21,    20,    37,
      22,    23,    14,    18,    19,     0,     0,     8,    44,    11,
      50,    50,    61,    66,    30,    36,    38,    39,    35,    27,
       0,    28,    32,    33,    34,     0,     0,    16,    17,    24,
      45,    46,     0,     0,    75,     0,     0,    69,     0,    64,
       0,     0,    68,    89,    87,     0,     0,    13,    59,     0,
       0,    53,     0,     0,     0,     0,     0,    62,    60,    66,
       0,    78,     0,    84,     0,     0,     0,     0,    26,    58,
       0,     0,    51,     0,    47,     0,    83,    85,   103,   104,
       0,    95,    98,   100,   102,    79,     0,    63,     0,    67,
       0,     0,    42,     0,    88,     0,     0,    55,    52,     0,
      73,     0,    74,     0,   107,   113,   116,   117,   114,   112,
     115,   105,   106,     0,     0,   111,   108,   109,   110,     0,
       0,     0,    86,    90,    41,    31,     0,     0,    54,    82,
      94,    99,    97,   101,    80,    59,    76,     0,    29,     0,
       0,     0,    40,    81,    59,    77,    66,    70,    72,     0,
       0,     0,    66,    71
  };

  const signed char
  parser::yypgoto_[] =
  {
    -108,  -108,  -108,  -108,  -108,  -108,    -8,    98,  -108,  -108,
      99,    83,   -54,   -16,  -108,  -108,    79,  -108,    64,  -108,
    -108,   -95,  -108,  -108,  -108,  -108,   -15,  -108,  -108,  -108,
    -108,  -108,   102,  -108,    40,   -66,   -60,  -108,   -14,  -108,
    -108,  -108,  -108,   -17,  -106,  -108,  -108,  -108,  -108,  -108,
      54,   -34,   -35,  -108,  -108,   -98,  -108,    97,    29,  -108,
      13,   -83,    -4,   -13,   -73,  -107,     4,    11,     1,  -108,
    -108,  -108
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     2,    17,     3,     4,    11,    99,    12,    13,    21,
      30,    52,    53,    68,    55,    56,    19,    27,    69,    70,
     176,    71,    72,    73,    74,   117,   143,    25,    37,    38,
      39,    40,    81,   100,   101,    20,    44,    80,    87,    42,
      63,   108,    88,     7,    89,   106,   199,    90,   187,   196,
     112,   136,   185,   194,   125,    91,   113,   114,   145,    92,
      82,    33,    24,   130,    34,   131,   132,   133,   134,   163,
     169,   164
  };

  const short int
  parser::yytable_[] =
  {
       9,    77,    78,   137,    28,   139,   126,    23,   124,    22,
      45,    41,    26,   107,    54,    96,   102,   122,   154,     1,
      58,    59,    15,   103,    46,   147,   161,   162,     8,   170,
      57,   171,    47,    18,    48,    60,    61,    75,   128,   120,
     129,   116,   150,    31,   146,     5,   180,   152,    32,     6,
      49,    43,   151,   179,   178,   102,     6,   153,   173,    93,
      54,   165,    14,   149,    94,    31,   -85,   153,   153,    32,
       6,   109,   166,   167,   168,     8,    50,    51,    10,   190,
     191,   188,    16,   121,   119,   144,   110,    32,   197,   174,
     198,     8,   177,   201,   123,     8,   203,     8,   104,   105,
     127,   140,   141,   -59,    14,    93,   115,    18,   -66,    84,
      35,    36,   -66,    84,    47,    84,    29,    62,    85,    86,
      48,    47,    85,    86,    85,    86,    94,   135,    64,    65,
      66,    67,    49,    43,   111,   192,    65,    66,    67,    49,
     142,   175,   184,   186,   193,    76,   154,   127,   155,   156,
     157,   158,   159,   160,   161,   162,   195,    79,    98,    97,
     118,   148,   189,    83,   138,   200,   202,    95,   182,   172,
     183,     0,     0,     0,   181,     0,     0,     0,     0,     0,
       0,    93,     0,     0,     0,     0,     0,     0,     0,     0,
      93,     0,    93,     0,     0,     0,     0,     0,    93
  };

  const short int
  parser::yycheck_[] =
  {
       4,    55,    56,   109,    21,   112,   104,    15,   103,    13,
      27,    25,    20,    18,    30,    75,    82,   100,    41,    12,
      37,    38,     9,    83,    28,   120,    49,    50,     9,   136,
      34,   138,     5,    14,     7,    39,    40,    45,     7,    99,
       9,    95,   125,    55,   117,     0,   153,   130,    59,    61,
      23,    62,   125,   151,   149,   121,    61,   130,   141,    63,
      76,    40,    54,   123,    56,    55,    58,   140,   141,    59,
      61,    88,    51,    52,    53,     9,    49,    50,    13,   185,
     187,   176,    60,   100,    98,    57,    90,    59,   194,   143,
     196,     9,   146,   200,   102,     9,   202,     9,    85,    86,
     104,   114,   115,    17,    54,   109,    93,    14,    26,    27,
      15,    16,    24,    27,     5,    27,    47,    17,    36,    37,
       7,     5,    36,    37,    36,    37,    56,    24,    19,    20,
      21,    22,    23,    62,    58,   189,    20,    21,    22,    23,
      39,    30,    25,    28,    26,    46,    41,   151,    43,    44,
      45,    46,    47,    48,    49,    50,    29,    59,    79,    76,
      96,   121,   177,    61,   110,   199,   201,    70,   164,   140,
     169,    -1,    -1,    -1,   163,    -1,    -1,    -1,    -1,    -1,
      -1,   185,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     194,    -1,   196,    -1,    -1,    -1,    -1,    -1,   202
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    12,    64,    66,    67,     0,    61,   106,     9,   125,
      13,    68,    70,    71,    54,   123,    60,    65,    14,    79,
      98,    72,   125,    69,   125,    90,    69,    80,   106,    47,
      73,    55,    59,   124,   127,    15,    16,    91,    92,    93,
      94,   101,   102,    62,    99,   106,   125,     5,     7,    23,
      49,    50,    74,    75,    76,    77,    78,   125,   106,   106,
     125,   125,    17,   103,    19,    20,    21,    22,    76,    81,
      82,    84,    85,    86,    87,    69,    73,    75,    75,    70,
     100,    95,   123,    95,    27,    36,    37,   101,   105,   107,
     110,   118,   122,   125,    56,   120,    99,    74,    79,    69,
      96,    97,    98,    99,   123,   123,   108,    18,   104,   106,
     125,    58,   113,   119,   120,   123,    75,    88,    81,   101,
      99,   106,   124,    69,    84,   117,   118,   125,     7,     9,
     126,   128,   129,   130,   131,    24,   114,   107,   113,   128,
     126,   126,    39,    89,    57,   121,   127,    84,    97,    99,
     124,   127,   124,   127,    41,    43,    44,    45,    46,    47,
      48,    49,    50,   132,   134,    40,    51,    52,    53,   133,
     128,   128,   121,   124,    75,    30,    83,    75,    84,   118,
     128,   130,   129,   131,    25,   115,    28,   111,    84,    89,
     107,   128,    75,    26,   116,    29,   112,   107,   107,   109,
     114,   128,   115,   107
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    63,    64,    65,    66,    66,    67,    68,    69,    69,
      70,    70,    71,    72,    72,    73,    74,    74,    74,    74,
      75,    76,    77,    78,    79,    79,    80,    80,    81,    81,
      82,    83,    84,    84,    84,    84,    85,    76,    86,    87,
      88,    88,    89,    90,    90,    91,    92,    92,    93,    94,
      95,    95,    96,    96,    97,    97,    98,    99,   100,   102,
     101,   103,   104,   105,   105,   106,   107,   107,   107,   108,
     109,   107,   107,   107,   107,   110,   111,   112,   113,   114,
     115,   116,   117,   117,   118,   119,   119,   120,   121,   122,
     122,   123,   124,   125,   126,   126,   127,   128,   128,   129,
     129,   130,   130,   131,   131,   132,   132,   132,   133,   133,
     133,   133,   134,   134,   134,   134,   134,   134
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     4,     1,     5,     2,     1,     4,     3,     1,
       3,     0,     1,     5,     3,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     0,     3,     5,     3,     1,     6,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     3,     1,     0,     3,     3,     3,     5,     1,     1,
       0,     3,     3,     1,     4,     3,     1,     1,     3,     0,
       4,     1,     1,     3,     1,     1,     0,     3,     1,     0,
       0,    13,     8,     4,     4,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     2,     0,     3,     1,     1,     1,
       4,     1,     1,     1,     3,     1,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
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
  "MARKER_LOGICAND", "MARKER_LOGICOR", "MARKER_LOGICNOT", "MARKER_NEQ",
  "MARKER_LE", "MARKER_GE", "MARKER_LT", "MARKER_EQ", "MARKER_GT",
  "MARKER_ADD", "MARKER_SUB", "MARKER_MUL", "MARKER_DIV", "MARKER_MOD",
  "MARKER_LPAREN", "MARKER_RPAREN", "MARKER_LBRACKET", "MARKER_RBRACKET",
  "MARKER_ASSIGN", "MARKER_COMMA", "MARKER_DOT", "MARKER_SEMICOLON",
  "MARKER_COLON", "$accept", "programstruct", "dot", "program_head",
  "program", "program_body", "idlist", "const_declarations", "const",
  "const_declaration", "eq", "const_value", "num", "char", "add", "sub",
  "var_declarations", "var_declaration", "type", "array", "of",
  "basic_type", "integer", "real", "boolean", "period", "range",
  "subprogram_declarations", "subprogram", "subprogram_head", "procedure",
  "function", "formal_parameter", "parameter_list", "parameter", "var",
  "colon", "subprogram_body", "compound_statement", "@1", "begin", "end",
  "statement_list", "semicolon", "statement", "@2", "@3", "for", "to",
  "do", "assign", "if", "then", "else", "variable_list", "variable",
  "id_varpart", "lbracket", "rbracket", "procedure_call", "lparen",
  "rparen", "id", "expression_list", "comma", "expression",
  "simple_expression", "term", "factor", "addop", "mulop", "relop", YY_NULLPTR
  };


  const unsigned short int
  parser::yyrline_[] =
  {
       0,    98,    98,   114,   121,   133,   145,   151,   170,   181,
     193,   201,   206,   213,   233,   257,   263,   264,   265,   266,
     270,   276,   282,   288,   294,   295,   307,   328,   350,   353,
     359,   365,   372,   373,   374,   375,   378,   384,   390,   396,
     403,   408,   414,   419,   420,   439,   452,   468,   486,   492,
     498,   499,   514,   526,   540,   552,   565,   572,   578,   595,
     595,   613,   619,   626,   642,   654,   659,   660,   661,   662,
     663,   662,   665,   666,   667,   670,   676,   682,   688,   693,
     699,   705,   712,   727,   740,   750,   751,   764,   769,   775,
     781,   796,   801,   806,   812,   826,   838,   844,   855,   859,
     860,   863,   864,   867,   871,   876,   880,   884,   890,   894,
     898,   902,   907,   911,   915,   919,   923,   927
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
       2,     2,    39,    40,    41,    42,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    43,
      44,    45,    46,    47,    48,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    49,    50,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      51,    52,    53,     2,     2,     2,     2,     2,     2,     2,
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
#line 2877 "yacc_bison.h" // lalr1.cc:1167
#line 931 "parser.y" // lalr1.cc:1168

