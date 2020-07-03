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
      yylast_ = 208,     ///< Last index in yytable_.
      yynnts_ = 74,  ///< Number of nonterminal symbols.
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
#line 264 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));}
#line 1328 "yacc_bison.h" // lalr1.cc:859
    break;

  case 17:
#line 265 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));}
#line 1334 "yacc_bison.h" // lalr1.cc:859
    break;

  case 18:
#line 266 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1340 "yacc_bison.h" // lalr1.cc:859
    break;

  case 19:
#line 267 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1346 "yacc_bison.h" // lalr1.cc:859
    break;

  case 20:
#line 271 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantInteger(((const ConstantInteger*)((yystack_[0].value))));
  // access_ast($$);
}
#line 1355 "yacc_bison.h" // lalr1.cc:859
    break;

  case 21:
#line 277 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantChar(((const ConstantChar*)((yystack_[0].value))));
  // access_ast($$);
}
#line 1364 "yacc_bison.h" // lalr1.cc:859
    break;

  case 22:
#line 283 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1373 "yacc_bison.h" // lalr1.cc:859
    break;

  case 23:
#line 289 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1382 "yacc_bison.h" // lalr1.cc:859
    break;

  case 24:
#line 295 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ExpVoid();  /* access_ast($$); */ }
#line 1388 "yacc_bison.h" // lalr1.cc:859
    break;

  case 25:
#line 296 "parser.y" // lalr1.cc:859
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
#line 308 "parser.y" // lalr1.cc:859
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
#line 329 "parser.y" // lalr1.cc:859
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
#line 351 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
}
#line 1458 "yacc_bison.h" // lalr1.cc:859
    break;

  case 29:
#line 354 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[3].value);
  ((ArrayTypeSpec*)(yylhs.value))->keyword = ((BasicTypeSpec*)(yystack_[0].value))->keyword;
}
#line 1467 "yacc_bison.h" // lalr1.cc:859
    break;

  case 30:
#line 360 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1476 "yacc_bison.h" // lalr1.cc:859
    break;

  case 31:
#line 366 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1485 "yacc_bison.h" // lalr1.cc:859
    break;

  case 32:
#line 373 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1491 "yacc_bison.h" // lalr1.cc:859
    break;

  case 33:
#line 374 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1497 "yacc_bison.h" // lalr1.cc:859
    break;

  case 34:
#line 375 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1503 "yacc_bison.h" // lalr1.cc:859
    break;

  case 35:
#line 376 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1509 "yacc_bison.h" // lalr1.cc:859
    break;

  case 36:
#line 379 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1518 "yacc_bison.h" // lalr1.cc:859
    break;

  case 37:
#line 385 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1527 "yacc_bison.h" // lalr1.cc:859
    break;

  case 38:
#line 391 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1536 "yacc_bison.h" // lalr1.cc:859
    break;

  case 39:
#line 397 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1545 "yacc_bison.h" // lalr1.cc:859
    break;

  case 40:
#line 404 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[4].value);
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)(yystack_[2].value), (int64_t)(yystack_[0].value)));
  //ast_reduce_nodes(5, Type::ArrayTypeSpec);
}
#line 1555 "yacc_bison.h" // lalr1.cc:859
    break;

  case 41:
#line 409 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ArrayTypeSpec();
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)(yystack_[2].value), (int64_t)(yystack_[0].value)));
  //ast_reduce_nodes(3, Type::ArrayTypeSpec);
}
#line 1565 "yacc_bison.h" // lalr1.cc:859
    break;

  case 42:
#line 415 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1574 "yacc_bison.h" // lalr1.cc:859
    break;

  case 43:
#line 420 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new SubprogramDecls();  }
#line 1580 "yacc_bison.h" // lalr1.cc:859
    break;

  case 44:
#line 421 "parser.y" // lalr1.cc:859
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
#line 440 "parser.y" // lalr1.cc:859
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
#line 453 "parser.y" // lalr1.cc:859
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
#line 469 "parser.y" // lalr1.cc:859
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
#line 487 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1665 "yacc_bison.h" // lalr1.cc:859
    break;

  case 49:
#line 493 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1674 "yacc_bison.h" // lalr1.cc:859
    break;

  case 50:
#line 499 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ParamList();  /* access_ast($$); */  }
#line 1680 "yacc_bison.h" // lalr1.cc:859
    break;

  case 51:
#line 500 "parser.y" // lalr1.cc:859
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
#line 515 "parser.y" // lalr1.cc:859
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
#line 527 "parser.y" // lalr1.cc:859
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
#line 541 "parser.y" // lalr1.cc:859
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
#line 553 "parser.y" // lalr1.cc:859
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
#line 566 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1766 "yacc_bison.h" // lalr1.cc:859
    break;

  case 57:
#line 573 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1775 "yacc_bison.h" // lalr1.cc:859
    break;

  case 58:
#line 579 "parser.y" // lalr1.cc:859
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
#line 597 "parser.y" // lalr1.cc:859
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
#line 1812 "yacc_bison.h" // lalr1.cc:859
    break;

  case 60:
#line 609 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new CompoundStatement(); }
#line 1818 "yacc_bison.h" // lalr1.cc:859
    break;

  case 61:
#line 615 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1827 "yacc_bison.h" // lalr1.cc:859
    break;

  case 62:
#line 621 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1836 "yacc_bison.h" // lalr1.cc:859
    break;

  case 63:
#line 628 "parser.y" // lalr1.cc:859
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
#line 644 "parser.y" // lalr1.cc:859
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
#line 656 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1880 "yacc_bison.h" // lalr1.cc:859
    break;

  case 66:
#line 661 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExpVoid();  }
#line 1886 "yacc_bison.h" // lalr1.cc:859
    break;

  case 67:
#line 662 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExecStatement(new ExpAssign((Variable*)(yystack_[2].value), (Exp*)(yystack_[0].value)));}
#line 1892 "yacc_bison.h" // lalr1.cc:859
    break;

  case 68:
#line 663 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new CompoundStatement();}
#line 1898 "yacc_bison.h" // lalr1.cc:859
    break;

  case 69:
#line 664 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new CompoundStatement();}
#line 1904 "yacc_bison.h" // lalr1.cc:859
    break;

  case 70:
#line 665 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new IfElseStatement();}
#line 1910 "yacc_bison.h" // lalr1.cc:859
    break;

  case 71:
#line 666 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new IfElseStatement();}
#line 1916 "yacc_bison.h" // lalr1.cc:859
    break;

  case 72:
#line 667 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ForStatement();}
#line 1922 "yacc_bison.h" // lalr1.cc:859
    break;

  case 73:
#line 668 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new Read();}
#line 1928 "yacc_bison.h" // lalr1.cc:859
    break;

  case 74:
#line 669 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new Write();}
#line 1934 "yacc_bison.h" // lalr1.cc:859
    break;

  case 75:
#line 672 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1943 "yacc_bison.h" // lalr1.cc:859
    break;

  case 76:
#line 678 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1952 "yacc_bison.h" // lalr1.cc:859
    break;

  case 77:
#line 684 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1961 "yacc_bison.h" // lalr1.cc:859
    break;

  case 78:
#line 690 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1970 "yacc_bison.h" // lalr1.cc:859
    break;

  case 79:
#line 695 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1979 "yacc_bison.h" // lalr1.cc:859
    break;

  case 80:
#line 701 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
  // access_ast($$);
}
#line 1988 "yacc_bison.h" // lalr1.cc:859
    break;

  case 81:
#line 707 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
    // access_ast($$);
}
#line 1997 "yacc_bison.h" // lalr1.cc:859
    break;

  case 82:
#line 714 "parser.y" // lalr1.cc:859
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
#line 729 "parser.y" // lalr1.cc:859
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
#line 742 "parser.y" // lalr1.cc:859
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
#line 752 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ExpressionList(); }
#line 2050 "yacc_bison.h" // lalr1.cc:859
    break;

  case 86:
#line 753 "parser.y" // lalr1.cc:859
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
#line 766 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2075 "yacc_bison.h" // lalr1.cc:859
    break;

  case 88:
#line 771 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2084 "yacc_bison.h" // lalr1.cc:859
    break;

  case 89:
#line 777 "parser.y" // lalr1.cc:859
    {
   (yylhs.value) = new ExpCall((const Identifier*)(yystack_[0].value), nullptr);
    //ast_reduce_nodes(1,Type::ExpCall);
  }
#line 2093 "yacc_bison.h" // lalr1.cc:859
    break;

  case 90:
#line 781 "parser.y" // lalr1.cc:859
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
#line 2109 "yacc_bison.h" // lalr1.cc:859
    break;

  case 91:
#line 797 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2118 "yacc_bison.h" // lalr1.cc:859
    break;

  case 92:
#line 802 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2127 "yacc_bison.h" // lalr1.cc:859
    break;

  case 93:
#line 807 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new Ident((const Identifier *)((yystack_[0].value)));
    // access_ast($$);
}
#line 2136 "yacc_bison.h" // lalr1.cc:859
    break;

  case 94:
#line 813 "parser.y" // lalr1.cc:859
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
#line 2155 "yacc_bison.h" // lalr1.cc:859
    break;

  case 95:
#line 827 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpressionList();
  ((ExpressionList*)(yylhs.value))->explist.push_back((Exp*)(yystack_[0].value));
    /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(1, Type::ExpressionList)); */

    /* Exp* exp = (Exp*)(node->children.front()); */
    /* node->explist.push_back(exp); */
    /* node->children.pop_front(); */
}
#line 2169 "yacc_bison.h" // lalr1.cc:859
    break;

  case 96:
#line 839 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
}
#line 2178 "yacc_bison.h" // lalr1.cc:859
    break;

  case 97:
#line 845 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpAssign((Exp*)(yystack_[2].value), (Exp*)(yystack_[0].value));
  // ast_reduce_nodes(3, Type::ExpAssign);
}
#line 2187 "yacc_bison.h" // lalr1.cc:859
    break;

  case 98:
#line 856 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2193 "yacc_bison.h" // lalr1.cc:859
    break;

  case 99:
#line 860 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value)); }
#line 2199 "yacc_bison.h" // lalr1.cc:859
    break;

  case 100:
#line 861 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2205 "yacc_bison.h" // lalr1.cc:859
    break;

  case 101:
#line 864 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value)); }
#line 2211 "yacc_bison.h" // lalr1.cc:859
    break;

  case 102:
#line 865 "parser.y" // lalr1.cc:859
    { (yylhs.value)=(yystack_[0].value); }
#line 2217 "yacc_bison.h" // lalr1.cc:859
    break;

  case 104:
#line 868 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
  }
#line 2225 "yacc_bison.h" // lalr1.cc:859
    break;

  case 105:
#line 871 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[3].value);
}
#line 2233 "yacc_bison.h" // lalr1.cc:859
    break;

  case 106:
#line 874 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2241 "yacc_bison.h" // lalr1.cc:859
    break;

  case 107:
#line 877 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2249 "yacc_bison.h" // lalr1.cc:859
    break;

  case 108:
#line 880 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
  }
#line 2257 "yacc_bison.h" // lalr1.cc:859
    break;

  case 109:
#line 884 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2265 "yacc_bison.h" // lalr1.cc:859
    break;

  case 110:
#line 888 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2273 "yacc_bison.h" // lalr1.cc:859
    break;

  case 111:
#line 892 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2282 "yacc_bison.h" // lalr1.cc:859
    break;

  case 112:
#line 896 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2291 "yacc_bison.h" // lalr1.cc:859
    break;

  case 113:
#line 900 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2300 "yacc_bison.h" // lalr1.cc:859
    break;

  case 114:
#line 906 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
}
#line 2309 "yacc_bison.h" // lalr1.cc:859
    break;

  case 115:
#line 910 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
  }
#line 2318 "yacc_bison.h" // lalr1.cc:859
    break;

  case 116:
#line 914 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
  }
#line 2327 "yacc_bison.h" // lalr1.cc:859
    break;

  case 117:
#line 918 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  // access_ast($$);
  }
#line 2336 "yacc_bison.h" // lalr1.cc:859
    break;

  case 118:
#line 923 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2345 "yacc_bison.h" // lalr1.cc:859
    break;

  case 119:
#line 927 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2354 "yacc_bison.h" // lalr1.cc:859
    break;

  case 120:
#line 931 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2363 "yacc_bison.h" // lalr1.cc:859
    break;

  case 121:
#line 935 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2372 "yacc_bison.h" // lalr1.cc:859
    break;

  case 122:
#line 939 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2381 "yacc_bison.h" // lalr1.cc:859
    break;

  case 123:
#line 943 "parser.y" // lalr1.cc:859
    {
    (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
    // access_ast($$);
  }
#line 2390 "yacc_bison.h" // lalr1.cc:859
    break;


#line 2394 "yacc_bison.h" // lalr1.cc:859
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


  const signed char parser::yypact_ninf_ = -103;

  const signed char parser::yytable_ninf_ = -86;

  const short int
  parser::yypact_[] =
  {
       1,  -103,    29,   -23,    37,  -103,  -103,    36,  -103,    20,
    -103,    28,    41,    37,  -103,    37,  -103,  -103,  -103,  -103,
      37,   -23,    39,    -7,  -103,   163,    -1,   -23,    37,  -103,
      52,  -103,  -103,  -103,    37,  -103,  -103,  -103,   -23,   -23,
      37,    37,  -103,   118,  -103,   154,    37,    39,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,    86,    86,  -103,  -103,
      36,    20,    20,  -103,    20,    20,  -103,    15,  -103,    37,
      42,  -103,    60,  -103,  -103,  -103,  -103,  -103,  -103,    49,
    -103,  -103,  -103,  -103,    -1,    52,  -103,  -103,    41,  -103,
    -103,    18,    35,    37,   108,    87,  -103,  -103,   118,    42,
    -103,   108,  -103,  -103,   108,   108,    86,   154,  -103,   105,
      -1,   -27,  -103,    37,   144,    -7,  -103,    49,  -103,   117,
    -103,  -103,    24,    -7,  -103,   143,    81,  -103,   108,   108,
    -103,   108,  -103,  -103,   108,  -103,    26,    -7,    90,    26,
    -103,  -103,   144,    18,  -103,    -1,  -103,  -103,    37,   108,
    -103,   108,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,   108,   108,  -103,  -103,  -103,  -103,   108,  -103,  -103,
     111,   109,  -103,  -103,  -103,  -103,    86,   110,    86,  -103,
    -103,   144,  -103,    -7,  -103,    81,    -6,  -103,  -103,   118,
    -103,   108,  -103,  -103,   144,    90,  -103,  -103,   115,   114,
    -103,    86,  -103,   118,  -103,   118,  -103,  -103,  -103,    87,
     108,   111,   118,  -103
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     6,     0,     0,     0,     1,    65,    11,    93,     5,
      12,     0,    24,     0,    91,     0,     3,     2,    56,    43,
       0,     0,     0,     0,     9,     0,     0,     0,    10,    15,
       0,    92,    96,     4,     0,    48,    49,    61,     0,     0,
       0,     0,     7,    66,    57,     0,    25,     0,    21,    20,
      37,    22,    23,    14,    18,    19,     0,     0,     8,    44,
      11,    50,    50,    75,     0,     0,    69,     0,    64,     0,
       0,    68,    89,    30,    36,    38,    39,    35,    27,     0,
      28,    32,    33,    34,     0,     0,    16,    17,    24,    45,
      46,     0,     0,     0,   103,     0,    62,    59,    66,     0,
      78,   103,    87,    84,   103,   103,     0,     0,    13,     0,
       0,     0,    53,     0,     0,     0,    83,    85,   109,   110,
     108,   104,    85,     0,    95,    98,   100,   102,   103,   103,
      79,   103,    60,    63,   103,    67,     0,     0,     0,     0,
      26,    58,     0,     0,    51,     0,    47,    73,     0,   103,
      74,   103,   113,   119,   122,   123,   120,   118,   121,   111,
     112,   103,   103,   117,   114,   115,   116,   103,   106,   107,
       0,     0,    88,    86,    90,    42,     0,     0,     0,    55,
      52,     0,    82,     0,    94,    99,    97,   101,    80,    66,
      76,   103,    41,    31,     0,     0,    54,   105,     0,     0,
      29,     0,    81,    66,    77,    66,    40,    70,    72,     0,
     103,     0,    66,    71
  };

  const signed char
  parser::yypgoto_[] =
  {
    -103,  -103,  -103,  -103,  -103,  -103,    -5,    92,  -103,  -103,
      99,   -12,   -53,   -43,  -103,  -103,    65,  -103,    53,  -103,
    -103,  -102,  -103,  -103,  -103,  -103,   -39,  -103,  -103,  -103,
    -103,  -103,   100,  -103,    25,   -71,   -15,  -103,   -19,  -103,
    -103,  -103,  -103,   -13,   -93,  -103,  -103,  -103,  -103,  -103,
      70,   -38,   -30,  -103,  -103,   -42,  -103,    93,    43,  -103,
      -2,   -92,    -4,   -83,   -55,   -84,    21,    33,   -25,  -103,
    -103,  -103,  -103,  -103
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     2,    17,     3,     4,    11,   110,    12,    13,    21,
      30,   120,    54,    55,    56,    57,    19,    27,    78,    79,
     194,    80,    81,    82,    83,   139,   176,    25,    38,    39,
      40,    41,    90,   111,   112,    20,    45,    89,    66,   132,
      43,    97,    67,     7,    68,    95,   209,    69,   191,   205,
     101,   131,   189,   203,   115,   121,   103,   104,   173,    71,
      91,    33,   122,   123,    34,   124,   125,   126,   127,   128,
     129,   161,   167,   162
  };

  const short int
  parser::yytable_[] =
  {
       9,    70,    77,    86,    87,   133,    42,    15,    28,    22,
      23,    24,   146,     1,    46,    26,    24,   135,    53,   144,
     113,   136,   137,   147,    47,    59,    60,     8,    31,     5,
      58,   150,    18,    96,     6,   152,    61,    62,     6,    72,
     179,    84,    24,   159,   160,   174,     8,   170,    31,    10,
     171,   116,    32,   138,    98,    18,    70,    48,    32,    49,
     148,    44,    93,    94,    77,    99,   183,   184,   151,   107,
     105,    77,   113,   108,    14,    50,     6,   114,    14,   196,
     102,   151,   151,   172,   178,    32,    29,    24,    16,   117,
     141,   197,   200,    49,    72,   142,   198,    44,   143,    77,
     100,    51,    52,   168,   169,   102,   182,   199,   145,    24,
     207,   130,   208,    48,    14,    49,   102,     8,   -85,   213,
     149,   163,    37,   192,   -23,   195,   211,     8,   151,   175,
     181,    50,   164,   165,   166,    37,   188,   190,    77,    24,
     193,   202,   187,   204,   117,    63,    85,    70,   206,    48,
     118,    77,    88,   109,    64,    65,   201,    51,   119,    48,
     140,    70,    92,    70,    74,    75,    76,    50,   180,   134,
      70,   210,   106,    73,    74,    75,    76,    50,    35,    36,
      37,   212,   177,   186,   152,    72,   153,   154,   155,   156,
     157,   158,   159,   160,   185,     0,     0,     0,     0,    72,
       0,    72,     0,     0,     0,     0,     0,     0,    72
  };

  const short int
  parser::yycheck_[] =
  {
       4,    43,    45,    56,    57,    98,    25,     9,    21,    13,
      15,    15,   114,    12,    27,    20,    20,   101,    30,   111,
      91,   104,   105,   115,    28,    38,    39,     9,    55,     0,
      34,   123,    14,    18,    61,    41,    40,    41,    61,    43,
     142,    46,    46,    49,    50,   137,     9,   131,    55,    13,
     134,    93,    59,   106,    67,    14,    98,     5,    59,     7,
     115,    62,    64,    65,   107,    69,   149,   151,   123,    84,
      72,   114,   143,    85,    54,    23,    61,    92,    54,   181,
      56,   136,   137,    57,   139,    59,    47,    91,    60,    93,
     109,   183,   194,     7,    98,   110,   189,    62,   111,   142,
      58,    49,    50,   128,   129,    56,   148,   191,   113,   113,
     203,    24,   205,     5,    54,     7,    56,     9,    58,   212,
     122,    40,    17,   176,     7,   178,   210,     9,   183,    39,
     145,    23,    51,    52,    53,    17,    25,    28,   181,   143,
      30,    26,   167,    29,   148,    27,    47,   189,   201,     5,
      42,   194,    60,    88,    36,    37,   195,    49,    50,     5,
     107,   203,    62,   205,    20,    21,    22,    23,   143,    99,
     212,   209,    79,    19,    20,    21,    22,    23,    15,    16,
      17,   211,   139,   162,    41,   189,    43,    44,    45,    46,
      47,    48,    49,    50,   161,    -1,    -1,    -1,    -1,   203,
      -1,   205,    -1,    -1,    -1,    -1,    -1,    -1,   212
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    12,    64,    66,    67,     0,    61,   106,     9,   125,
      13,    68,    70,    71,    54,   123,    60,    65,    14,    79,
      98,    72,   125,    69,   125,    90,    69,    80,   106,    47,
      73,    55,    59,   124,   127,    15,    16,    17,    91,    92,
      93,    94,   101,   103,    62,    99,   106,   125,     5,     7,
      23,    49,    50,    74,    75,    76,    77,    78,   125,   106,
     106,   125,   125,    27,    36,    37,   101,   105,   107,   110,
     118,   122,   125,    19,    20,    21,    22,    76,    81,    82,
      84,    85,    86,    87,    69,    73,    75,    75,    70,   100,
      95,   123,    95,   123,   123,   108,    18,   104,   106,   125,
      58,   113,    56,   119,   120,   123,   120,    99,    74,    79,
      69,    96,    97,    98,    99,   117,   118,   125,    42,    50,
      74,   118,   125,   126,   128,   129,   130,   131,   132,   133,
      24,   114,   102,   107,   113,   128,   126,   126,    75,    88,
      81,   101,    99,   106,   124,    69,    84,   124,   127,   123,
     124,   127,    41,    43,    44,    45,    46,    47,    48,    49,
      50,   134,   136,    40,    51,    52,    53,   135,   131,   131,
     128,   128,    57,   121,   124,    39,    89,   121,   127,    84,
      97,    99,   118,   126,   128,   130,   129,   131,    25,   115,
      28,   111,    75,    30,    83,    75,    84,   124,   107,   128,
      84,    89,    26,   116,    29,   112,    75,   107,   107,   109,
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
     129,   130,   130,   131,   131,   131,   131,   131,   131,   132,
     133,   134,   134,   134,   135,   135,   135,   135,   136,   136,
     136,   136,   136,   136
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
       1,     3,     1,     0,     1,     4,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
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
  "simple_expression", "term", "factor", "not", "unimus", "addop", "mulop",
  "relop", YY_NULLPTR
  };


  const unsigned short int
  parser::yyrline_[] =
  {
       0,    98,    98,   114,   121,   133,   145,   151,   170,   181,
     193,   201,   206,   213,   233,   257,   264,   265,   266,   267,
     271,   277,   283,   289,   295,   296,   308,   329,   351,   354,
     360,   366,   373,   374,   375,   376,   379,   385,   391,   397,
     404,   409,   415,   420,   421,   440,   453,   469,   487,   493,
     499,   500,   515,   527,   541,   553,   566,   573,   579,   597,
     597,   615,   621,   628,   644,   656,   661,   662,   663,   664,
     665,   664,   667,   668,   669,   672,   678,   684,   690,   695,
     701,   707,   714,   729,   742,   752,   753,   766,   771,   777,
     781,   797,   802,   807,   813,   827,   839,   845,   856,   860,
     861,   864,   865,   867,   868,   871,   874,   877,   880,   884,
     888,   892,   896,   900,   906,   910,   914,   918,   923,   927,
     931,   935,   939,   943
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
#line 2923 "yacc_bison.h" // lalr1.cc:1167
#line 947 "parser.y" // lalr1.cc:1168

