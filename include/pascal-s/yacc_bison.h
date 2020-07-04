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
      yylast_ = 209,     ///< Last index in yytable_.
      yynnts_ = 72,  ///< Number of nonterminal symbols.
      yyfinal_ = 5, ///< Termination state number.
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
  // printf("%x %d %d\n", $$, ((Program*)$$)->type, ((Node*)$$)->type);
  access_ast((yylhs.value));
  //printf("finish!\n");
  /* Program *node = reinterpret_cast<Program*> (ast_reduce_nodes(4, Type::Program)); */
  /* node->programHead = (ProgramHead*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop semicolon */
  /* node->programBody = (ProgramBody*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop dot */
 }
#line 1141 "yacc_bison.h" // lalr1.cc:859
    break;

  case 3:
#line 101 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
 }
#line 1149 "yacc_bison.h" // lalr1.cc:859
    break;

  case 4:
#line 109 "parser.y" // lalr1.cc:859
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
#line 1166 "yacc_bison.h" // lalr1.cc:859
    break;

  case 5:
#line 121 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ProgramHead((const ExpKeyword*)(yystack_[1].value), new Ident((const Identifier*)(yystack_[0].value)));
}
#line 1174 "yacc_bison.h" // lalr1.cc:859
    break;

  case 6:
#line 124 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ProgramHead((const ExpKeyword*)(yystack_[3].value), new Ident((const Identifier*)(yystack_[2].value)));
}
#line 1182 "yacc_bison.h" // lalr1.cc:859
    break;

  case 7:
#line 131 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1190 "yacc_bison.h" // lalr1.cc:859
    break;

  case 8:
#line 136 "parser.y" // lalr1.cc:859
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
#line 1211 "yacc_bison.h" // lalr1.cc:859
    break;

  case 9:
#line 155 "parser.y" // lalr1.cc:859
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
#line 1227 "yacc_bison.h" // lalr1.cc:859
    break;

  case 10:
#line 166 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new IdentList();
  ((IdentList*)(yylhs.value))->idents.push_back((Identifier*)(yystack_[0].value));
  /* IdentList* node = reinterpret_cast<IdentList*> (ast_reduce_nodes(1, Type::IdentList)); */
  /* Identifier* id = (Identifier*)(node->children.front()); */
  /* node->idents.push_back(id); */
  /* node->children.pop_front(); */
  }
#line 1240 "yacc_bison.h" // lalr1.cc:859
    break;

  case 11:
#line 178 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
  /* ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(3, Type::ConstDecls)); */
  /* node->children.pop_front();// pop const */
  /* node->decls = reinterpret_cast<ConstDecls*>(node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */
}
#line 1253 "yacc_bison.h" // lalr1.cc:859
    break;

  case 12:
#line 186 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new ConstDecls(); }
#line 1259 "yacc_bison.h" // lalr1.cc:859
    break;

  case 13:
#line 191 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1267 "yacc_bison.h" // lalr1.cc:859
    break;

  case 14:
#line 197 "parser.y" // lalr1.cc:859
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
#line 1292 "yacc_bison.h" // lalr1.cc:859
    break;

  case 15:
#line 217 "parser.y" // lalr1.cc:859
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
#line 1318 "yacc_bison.h" // lalr1.cc:859
    break;

  case 16:
#line 241 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1326 "yacc_bison.h" // lalr1.cc:859
    break;

  case 17:
#line 247 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));}
#line 1332 "yacc_bison.h" // lalr1.cc:859
    break;

  case 18:
#line 248 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));}
#line 1338 "yacc_bison.h" // lalr1.cc:859
    break;

  case 19:
#line 249 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1344 "yacc_bison.h" // lalr1.cc:859
    break;

  case 20:
#line 250 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1350 "yacc_bison.h" // lalr1.cc:859
    break;

  case 21:
#line 251 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1356 "yacc_bison.h" // lalr1.cc:859
    break;

  case 22:
#line 254 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExpConstantBoolean(((const ConstantBoolean*)((yystack_[0].value))));}
#line 1362 "yacc_bison.h" // lalr1.cc:859
    break;

  case 23:
#line 256 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantInteger(((const ConstantInteger*)((yystack_[0].value))));
}
#line 1370 "yacc_bison.h" // lalr1.cc:859
    break;

  case 24:
#line 261 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpConstantChar(((const ConstantChar*)((yystack_[0].value))));
}
#line 1378 "yacc_bison.h" // lalr1.cc:859
    break;

  case 25:
#line 266 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1386 "yacc_bison.h" // lalr1.cc:859
    break;

  case 26:
#line 271 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1394 "yacc_bison.h" // lalr1.cc:859
    break;

  case 27:
#line 276 "parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr;  /* new ExpVoid(); */ }
#line 1400 "yacc_bison.h" // lalr1.cc:859
    break;

  case 28:
#line 277 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
  /* VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(3, Type::VarDecls)); */
  /* node->children.pop_front();// pop var */
  /* node->decls = reinterpret_cast<VarDecls*>(node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */
}
#line 1413 "yacc_bison.h" // lalr1.cc:859
    break;

  case 29:
#line 289 "parser.y" // lalr1.cc:859
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
#line 1439 "yacc_bison.h" // lalr1.cc:859
    break;

  case 30:
#line 310 "parser.y" // lalr1.cc:859
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
#line 1462 "yacc_bison.h" // lalr1.cc:859
    break;

  case 31:
#line 332 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
}
#line 1470 "yacc_bison.h" // lalr1.cc:859
    break;

  case 32:
#line 335 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[3].value);
  ((ArrayTypeSpec*)(yylhs.value))->keyword = ((BasicTypeSpec*)(yystack_[0].value))->keyword;
}
#line 1479 "yacc_bison.h" // lalr1.cc:859
    break;

  case 33:
#line 341 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1487 "yacc_bison.h" // lalr1.cc:859
    break;

  case 34:
#line 346 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1495 "yacc_bison.h" // lalr1.cc:859
    break;

  case 35:
#line 352 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1501 "yacc_bison.h" // lalr1.cc:859
    break;

  case 36:
#line 353 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1507 "yacc_bison.h" // lalr1.cc:859
    break;

  case 37:
#line 354 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1513 "yacc_bison.h" // lalr1.cc:859
    break;

  case 38:
#line 355 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1519 "yacc_bison.h" // lalr1.cc:859
    break;

  case 39:
#line 358 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1527 "yacc_bison.h" // lalr1.cc:859
    break;

  case 40:
#line 363 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1535 "yacc_bison.h" // lalr1.cc:859
    break;

  case 41:
#line 368 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1543 "yacc_bison.h" // lalr1.cc:859
    break;

  case 42:
#line 373 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BasicTypeSpec((const Keyword *)((yystack_[0].value)));
}
#line 1551 "yacc_bison.h" // lalr1.cc:859
    break;

  case 43:
#line 379 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[4].value);
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)(yystack_[2].value))->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)(yystack_[0].value))->value)->attr)));
  //ast_reduce_nodes(5, Type::ArrayTypeSpec);
}
#line 1561 "yacc_bison.h" // lalr1.cc:859
    break;

  case 44:
#line 384 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ArrayTypeSpec(nullptr);
  ((ArrayTypeSpec*)(yylhs.value))->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)(yystack_[2].value))->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)(yystack_[0].value))->value)->attr)));
  //ast_reduce_nodes(3, Type::ArrayTypeSpec);
}
#line 1571 "yacc_bison.h" // lalr1.cc:859
    break;

  case 45:
#line 389 "parser.y" // lalr1.cc:859
    {
    pascal_s::Pos* pos = ((Node*)(yystack_[3].value))->visit_pos();
    //printf("%d\n",yychar);
    #define cur_node (reinterpret_cast<const ast::ExpMarker*>((yystack_[2].value)))
    printf("\nperiod parse failed at line:%d column:%d: expect: num but got %s\n", pos->line,pos->column+pos->length+1,convertToString(cur_node->value).c_str());
    #undef  cur_node
    //printf("the error occur at line:%d   column:%d\n", pos->line,pos->column+pos->length+1);
    yyerrok;
}
#line 1585 "yacc_bison.h" // lalr1.cc:859
    break;

  case 46:
#line 399 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1593 "yacc_bison.h" // lalr1.cc:859
    break;

  case 47:
#line 404 "parser.y" // lalr1.cc:859
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
#line 1613 "yacc_bison.h" // lalr1.cc:859
    break;

  case 48:
#line 419 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new SubprogramDecls();  }
#line 1619 "yacc_bison.h" // lalr1.cc:859
    break;

  case 49:
#line 424 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Subprogram((SubprogramHead*)(yystack_[2].value), (SubprogramBody*)(yystack_[0].value));
  /* Subprogram* node = reinterpret_cast<Subprogram*> (ast_reduce_nodes(3, Type::Subprogram)); */
  /* node->subhead = (SubprogramHead*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */
  /* node->subbody = (SubprogramBody*)(node->children.front()); */
  /* node->children.pop_front(); */
}
#line 1633 "yacc_bison.h" // lalr1.cc:859
    break;

  case 50:
#line 437 "parser.y" // lalr1.cc:859
    {
  // printf("subpro head \n\n");
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
#line 1655 "yacc_bison.h" // lalr1.cc:859
    break;

  case 51:
#line 454 "parser.y" // lalr1.cc:859
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
#line 1676 "yacc_bison.h" // lalr1.cc:859
    break;

  case 52:
#line 472 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1684 "yacc_bison.h" // lalr1.cc:859
    break;

  case 53:
#line 477 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1692 "yacc_bison.h" // lalr1.cc:859
    break;

  case 54:
#line 482 "parser.y" // lalr1.cc:859
    { (yylhs.value) =  nullptr; /* new ParamList(); */  }
#line 1698 "yacc_bison.h" // lalr1.cc:859
    break;

  case 55:
#line 483 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(3, Type::ParamList)); */
  /* node->children.pop_front();//pop lparen */
  /* node->params = reinterpret_cast<ParamList*>(node->children.front())->params; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop rparen */
  //ast_reduce_nodes(3, Type::ParamList);
}
#line 1712 "yacc_bison.h" // lalr1.cc:859
    break;

  case 56:
#line 498 "parser.y" // lalr1.cc:859
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
#line 1729 "yacc_bison.h" // lalr1.cc:859
    break;

  case 57:
#line 510 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamList();
  ((ParamList*)(yylhs.value))->params.push_back((ParamSpec*)(yystack_[0].value));
  /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(1, Type::ParamList)); */
  /* ParamSpec* param = (ParamSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->params.push_back(param); */
  //$$ = $1;
  }
#line 1743 "yacc_bison.h" // lalr1.cc:859
    break;

  case 58:
#line 524 "parser.y" // lalr1.cc:859
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
#line 1760 "yacc_bison.h" // lalr1.cc:859
    break;

  case 59:
#line 536 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ParamSpec(nullptr, (IdentList*)(yystack_[2].value), (TypeSpec*)(yystack_[0].value));
  /* ParamSpec* node = reinterpret_cast<ParamSpec*> (ast_reduce_nodes(3, Type::ParamSpec)); */

  /* node->id_list = (IdentList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop colon */
  /* node->spec = (TypeSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
}
#line 1775 "yacc_bison.h" // lalr1.cc:859
    break;

  case 60:
#line 549 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1783 "yacc_bison.h" // lalr1.cc:859
    break;

  case 61:
#line 555 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1791 "yacc_bison.h" // lalr1.cc:859
    break;

  case 62:
#line 560 "parser.y" // lalr1.cc:859
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
#line 1811 "yacc_bison.h" // lalr1.cc:859
    break;

  case 63:
#line 577 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new CompoundStatement(); }
#line 1817 "yacc_bison.h" // lalr1.cc:859
    break;

  case 64:
#line 578 "parser.y" // lalr1.cc:859
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
#line 1834 "yacc_bison.h" // lalr1.cc:859
    break;

  case 65:
#line 595 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1842 "yacc_bison.h" // lalr1.cc:859
    break;

  case 66:
#line 600 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
             }
#line 1850 "yacc_bison.h" // lalr1.cc:859
    break;

  case 67:
#line 606 "parser.y" // lalr1.cc:859
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
#line 1871 "yacc_bison.h" // lalr1.cc:859
    break;

  case 68:
#line 622 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new StatementList();
  ((StatementList*)(yylhs.value))->statement.push_back((Statement*)(yystack_[0].value));
  /* StatementList* node = reinterpret_cast<StatementList*> (ast_reduce_nodes(1, Type::StatementList)); */

  /* Statement* sta = (Statement*)(node->children.front()); */
  /* node->statement.push_back(sta); */
  /* node->children.pop_front(); */
  }
#line 1885 "yacc_bison.h" // lalr1.cc:859
    break;

  case 69:
#line 634 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1893 "yacc_bison.h" // lalr1.cc:859
    break;

  case 70:
#line 639 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExecStatement(new ExpAssign((Variable*)(yystack_[2].value), (Exp*)(yystack_[0].value)));}
#line 1899 "yacc_bison.h" // lalr1.cc:859
    break;

  case 71:
#line 640 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ExecStatement((Exp*)(yystack_[0].value));}
#line 1905 "yacc_bison.h" // lalr1.cc:859
    break;

  case 72:
#line 641 "parser.y" // lalr1.cc:859
    {(yylhs.value) = (yystack_[0].value);}
#line 1911 "yacc_bison.h" // lalr1.cc:859
    break;

  case 73:
#line 642 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new IfElseStatement((Exp*)(yystack_[4].value), (Statement*)(yystack_[2].value), (Statement*)(yystack_[0].value));}
#line 1917 "yacc_bison.h" // lalr1.cc:859
    break;

  case 74:
#line 643 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new IfElseStatement((Exp*)(yystack_[2].value), (Statement*)(yystack_[0].value), nullptr);}
#line 1923 "yacc_bison.h" // lalr1.cc:859
    break;

  case 75:
#line 644 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new ForStatement((const Identifier *)(yystack_[6].value), (Exp*)(yystack_[4].value), (Exp*)(yystack_[2].value), (Statement*)(yystack_[0].value));}
#line 1929 "yacc_bison.h" // lalr1.cc:859
    break;

  case 76:
#line 645 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new Read((VariableList*)(yystack_[1].value));}
#line 1935 "yacc_bison.h" // lalr1.cc:859
    break;

  case 77:
#line 646 "parser.y" // lalr1.cc:859
    {(yylhs.value) = new Write((ExpressionList*)(yystack_[1].value));}
#line 1941 "yacc_bison.h" // lalr1.cc:859
    break;

  case 78:
#line 649 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1949 "yacc_bison.h" // lalr1.cc:859
    break;

  case 79:
#line 654 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1957 "yacc_bison.h" // lalr1.cc:859
    break;

  case 80:
#line 659 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
   }
#line 1965 "yacc_bison.h" // lalr1.cc:859
    break;

  case 81:
#line 664 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 1973 "yacc_bison.h" // lalr1.cc:859
    break;

  case 82:
#line 668 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1981 "yacc_bison.h" // lalr1.cc:859
    break;

  case 83:
#line 673 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
}
#line 1989 "yacc_bison.h" // lalr1.cc:859
    break;

  case 84:
#line 678 "parser.y" // lalr1.cc:859
    {
   (yylhs.value) = new ExpKeyword((const Keyword *)((yystack_[0].value)));
        }
#line 1997 "yacc_bison.h" // lalr1.cc:859
    break;

  case 85:
#line 684 "parser.y" // lalr1.cc:859
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

  case 86:
#line 699 "parser.y" // lalr1.cc:859
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

  case 87:
#line 712 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new Variable((Identifier*)(yystack_[1].value), (ExpressionList*)(yystack_[0].value));
  if( (yystack_[0].value) == nullptr ){
    ast::copy_pos_with_check((Variable*)(yylhs.value), (Identifier*)(yystack_[1].value));
  }else{
    ast::copy_pos_between_tokens((Variable*)(yylhs.value), (Identifier*)(yystack_[1].value), (ExpressionList*)(yystack_[0].value));
  }
}
#line 2044 "yacc_bison.h" // lalr1.cc:859
    break;

  case 88:
#line 722 "parser.y" // lalr1.cc:859
    { (yylhs.value) = nullptr; /* new ExpressionList(); */ }
#line 2050 "yacc_bison.h" // lalr1.cc:859
    break;

  case 89:
#line 723 "parser.y" // lalr1.cc:859
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

  case 90:
#line 736 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2074 "yacc_bison.h" // lalr1.cc:859
    break;

  case 91:
#line 740 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2082 "yacc_bison.h" // lalr1.cc:859
    break;

  case 92:
#line 745 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpCall((const Identifier*)(yystack_[0].value), nullptr);
}
#line 2090 "yacc_bison.h" // lalr1.cc:859
    break;

  case 93:
#line 748 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpCall((const Identifier*)(yystack_[3].value), (ExpressionList*)(yystack_[1].value));
}
#line 2098 "yacc_bison.h" // lalr1.cc:859
    break;

  case 94:
#line 756 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2106 "yacc_bison.h" // lalr1.cc:859
    break;

  case 95:
#line 760 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2114 "yacc_bison.h" // lalr1.cc:859
    break;

  case 96:
#line 764 "parser.y" // lalr1.cc:859
    {
  // $$ = new Ident((const Identifier *)($1));
  (yylhs.value) = (yystack_[0].value);
}
#line 2123 "yacc_bison.h" // lalr1.cc:859
    break;

  case 97:
#line 770 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[2].value);
  ((ExpressionList*)(yylhs.value))->explist.push_back((Exp*)(yystack_[0].value));
  ast::copy_pos_with_check((ExpressionList*)(yylhs.value), (Exp*)(yystack_[0].value));
  /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(3, Type::ExpressionList)); */

  /* node->explist = reinterpret_cast<ExpressionList*> (node->children.front())->explist; */
  /* node->children.pop_front(); */

  /* node->children.pop_front();// pop comma */

  /* Exp* exp = (Exp*)(node->children.front()); */
  /* node->explist.push_back(exp); */
  /* node->children.pop_front(); */
}
#line 2143 "yacc_bison.h" // lalr1.cc:859
    break;

  case 98:
#line 785 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpressionList();
  ((ExpressionList*)(yylhs.value))->explist.push_back((Exp*)(yystack_[0].value));
  ast::copy_pos_with_check((ExpressionList*)(yylhs.value), (Exp*)(yystack_[0].value));
  /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(1, Type::ExpressionList)); */

  /* Exp* exp = (Exp*)(node->children.front()); */
  /* node->explist.push_back(exp); */
  /* node->children.pop_front(); */
  }
#line 2158 "yacc_bison.h" // lalr1.cc:859
    break;

  case 99:
#line 798 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2166 "yacc_bison.h" // lalr1.cc:859
    break;

  case 100:
#line 803 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2174 "yacc_bison.h" // lalr1.cc:859
    break;

  case 101:
#line 806 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2180 "yacc_bison.h" // lalr1.cc:859
    break;

  case 102:
#line 810 "parser.y" // lalr1.cc:859
    { (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value)); }
#line 2186 "yacc_bison.h" // lalr1.cc:859
    break;

  case 103:
#line 811 "parser.y" // lalr1.cc:859
    { (yylhs.value) = (yystack_[0].value); }
#line 2192 "yacc_bison.h" // lalr1.cc:859
    break;

  case 104:
#line 814 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new BiExp((Exp*)(yystack_[2].value), (const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2200 "yacc_bison.h" // lalr1.cc:859
    break;

  case 105:
#line 817 "parser.y" // lalr1.cc:859
    { (yylhs.value)=(yystack_[0].value); }
#line 2206 "yacc_bison.h" // lalr1.cc:859
    break;

  case 107:
#line 820 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
}
#line 2214 "yacc_bison.h" // lalr1.cc:859
    break;

  case 108:
#line 823 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpCall((const Identifier*)(yystack_[3].value), (ExpressionList*)(yystack_[1].value));
}
#line 2222 "yacc_bison.h" // lalr1.cc:859
    break;

  case 109:
#line 826 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[1].value);
}
#line 2230 "yacc_bison.h" // lalr1.cc:859
    break;

  case 110:
#line 829 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2238 "yacc_bison.h" // lalr1.cc:859
    break;

  case 111:
#line 832 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new UnExp((const Marker*)(yystack_[1].value), (Exp*)(yystack_[0].value));
}
#line 2246 "yacc_bison.h" // lalr1.cc:859
    break;

  case 112:
#line 835 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = (yystack_[0].value);
  }
#line 2254 "yacc_bison.h" // lalr1.cc:859
    break;

  case 113:
#line 839 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2262 "yacc_bison.h" // lalr1.cc:859
    break;

  case 114:
#line 843 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2270 "yacc_bison.h" // lalr1.cc:859
    break;

  case 115:
#line 847 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2278 "yacc_bison.h" // lalr1.cc:859
    break;

  case 116:
#line 850 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2286 "yacc_bison.h" // lalr1.cc:859
    break;

  case 117:
#line 853 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2294 "yacc_bison.h" // lalr1.cc:859
    break;

  case 118:
#line 858 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2302 "yacc_bison.h" // lalr1.cc:859
    break;

  case 119:
#line 861 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2310 "yacc_bison.h" // lalr1.cc:859
    break;

  case 120:
#line 864 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2318 "yacc_bison.h" // lalr1.cc:859
    break;

  case 121:
#line 867 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2326 "yacc_bison.h" // lalr1.cc:859
    break;

  case 122:
#line 871 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
}
#line 2334 "yacc_bison.h" // lalr1.cc:859
    break;

  case 123:
#line 874 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2342 "yacc_bison.h" // lalr1.cc:859
    break;

  case 124:
#line 877 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2350 "yacc_bison.h" // lalr1.cc:859
    break;

  case 125:
#line 880 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2358 "yacc_bison.h" // lalr1.cc:859
    break;

  case 126:
#line 883 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2366 "yacc_bison.h" // lalr1.cc:859
    break;

  case 127:
#line 886 "parser.y" // lalr1.cc:859
    {
  (yylhs.value) = new ExpMarker((const Marker *)((yystack_[0].value)));
  }
#line 2374 "yacc_bison.h" // lalr1.cc:859
    break;


#line 2378 "yacc_bison.h" // lalr1.cc:859
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


  const signed char parser::yypact_ninf_ = -104;

  const signed char parser::yytable_ninf_ = -89;

  const short int
  parser::yypact_[] =
  {
      22,  -104,    41,   -14,    43,  -104,  -104,    46,  -104,     6,
    -104,     4,    54,    43,  -104,    10,  -104,  -104,  -104,  -104,
      43,   -14,    24,  -104,    -7,  -104,  -104,    63,    29,   -14,
      43,  -104,    95,  -104,  -104,    43,  -104,  -104,  -104,   -14,
     -14,    43,    43,  -104,   144,  -104,   155,    43,    24,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,    67,
      67,  -104,  -104,    46,     6,     6,  -104,  -104,     6,     6,
    -104,     9,  -104,    43,   125,    26,  -104,    -3,  -104,  -104,
    -104,  -104,  -104,  -104,    37,  -104,  -104,  -104,  -104,    29,
      95,  -104,  -104,    54,  -104,  -104,    16,    33,    43,   125,
    -104,  -104,   144,    26,  -104,   103,  -104,  -104,   125,   -34,
      86,   153,   137,  -104,   125,   125,  -104,   125,  -104,  -104,
     125,   125,    67,   155,  -104,    96,    29,   -18,  -104,    43,
     163,    -7,  -104,    37,    -7,  -104,  -104,   125,    -7,   125,
    -104,   144,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,   125,   125,  -104,  -104,  -104,  -104,   125,  -104,  -104,
    -104,   -17,    -7,    75,   -17,  -104,  -104,   163,    16,  -104,
      29,  -104,  -104,    43,  -104,   125,    89,  -104,    -7,    98,
     137,   156,  -104,  -104,  -104,  -104,  -104,    23,    92,    67,
    -104,  -104,   163,  -104,  -104,  -104,   125,  -104,  -104,   144,
    -104,  -104,    67,  -104,   163,    75,  -104,   108,  -104,   128,
    -104,    67,  -104,   144,  -104,  -104,  -104
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     7,     0,     0,     0,     1,    69,    12,    96,     5,
      13,     0,    27,     0,    94,     0,     3,     2,    60,    48,
       0,     0,     0,    95,     0,     6,    10,    63,     0,     0,
      11,    16,     0,    99,     4,     0,    52,    53,    65,     0,
       0,     0,     0,     8,    63,    61,     0,    28,     0,    24,
      23,    22,    40,    25,    26,    15,    21,    19,    20,     0,
       0,     9,    47,    12,    54,    54,    82,    78,     0,     0,
      72,     0,    68,     0,   106,     0,    71,    92,    33,    39,
      41,    42,    38,    30,     0,    31,    35,    36,    37,     0,
       0,    17,    18,    27,    49,    50,     0,     0,     0,   106,
      66,    64,    63,     0,   113,   114,   112,   107,   106,    88,
       0,   101,   103,   105,   106,   106,    81,   106,    90,    87,
     106,   106,     0,     0,    14,    63,     0,     0,    57,     0,
       0,     0,    86,    88,     0,    98,    67,   106,     0,   106,
      83,    63,   123,   126,   127,   124,   122,   125,   115,   116,
     117,   106,   106,   118,   119,   120,   121,   106,   110,   111,
      70,     0,     0,     0,     0,    29,    62,     0,     0,    55,
       0,    51,    76,     0,    77,   106,     0,   109,     0,    74,
     102,   100,   104,    91,    89,    93,    46,     0,     0,     0,
      59,    56,     0,    85,    97,    79,   106,   108,    84,    63,
     114,    44,     0,    34,     0,     0,    58,     0,    73,     0,
      32,     0,    80,    63,    45,    43,    75
  };

  const signed char
  parser::yypgoto_[] =
  {
    -104,  -104,  -104,  -104,  -104,  -104,   -12,    77,  -104,  -104,
     100,   -15,  -104,   -46,   -45,  -104,  -104,    53,  -104,    28,
    -104,  -104,  -103,  -104,  -104,  -104,  -104,   -56,  -104,  -104,
    -104,  -104,  -104,    90,  -104,    -2,   -89,   -79,  -104,   -21,
    -104,  -104,  -104,    -6,   -90,  -104,  -104,  -104,    51,  -104,
    -104,  -104,  -104,   -42,  -104,    78,     8,  -104,    19,   -20,
      -4,   -62,   -26,   -69,    32,    42,   -94,  -104,     7,  -104,
    -104,  -104
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     2,    17,     3,     4,    11,   126,    12,    13,    21,
      32,   106,    56,    57,    58,    59,    60,    19,    29,    83,
      84,   204,    85,    86,    87,    88,   164,   187,    27,    39,
      40,    41,    42,    95,   127,   128,    20,    46,    94,    70,
      44,   101,    71,     7,    72,    73,   196,   213,   117,    74,
     141,   199,   131,   107,   119,   120,   184,    76,   108,    25,
     109,   134,    35,   135,   111,   112,   113,   114,   115,   151,
     157,   152
  };

  const short int
  parser::yytable_[] =
  {
       9,    82,    75,    24,    34,   110,    43,   129,    28,    22,
     123,    26,   136,    91,    92,    30,    26,    55,   130,     8,
     158,   159,    14,    47,   118,     8,    48,   171,    15,   100,
      50,    61,    18,    62,    63,    89,     1,    64,    65,    23,
      77,     5,   183,    26,    33,     6,   138,   167,   160,     6,
      23,   179,     8,    14,    33,   118,   132,   -88,   161,   162,
      75,    10,    14,   182,   190,   102,    16,    23,   176,   103,
      18,    31,     6,   200,    50,   124,   163,   178,    82,   129,
      36,    37,    38,    96,    96,    82,   116,    98,    99,   206,
      33,   192,    26,    45,   133,   118,   121,    45,    77,    75,
      49,   210,    50,    51,   166,   173,   194,   169,   175,   208,
     -26,   172,   175,   140,   174,    38,   186,   170,   177,   195,
      52,   168,    82,   216,   203,    26,   198,   207,   139,   214,
      49,   193,    50,    51,     8,   175,   175,    77,   189,   212,
      93,   201,   185,   205,    53,    54,   125,    82,    90,   211,
      52,   165,   175,     8,   137,    97,   209,    75,   197,    82,
      49,     0,   122,    38,    26,   215,   191,   104,    49,   133,
      66,    75,   188,    67,    53,   105,    78,    79,    80,    81,
      52,    14,    68,    69,   181,    79,    80,    81,    52,   153,
     154,   155,   156,   180,   202,    77,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   148,   149,   150,     0,    77
  };

  const short int
  parser::yycheck_[] =
  {
       4,    46,    44,    15,    24,    74,    27,    96,    20,    13,
      89,    15,   102,    59,    60,    21,    20,    32,    97,     9,
     114,   115,    56,    29,    58,     9,    30,   130,     9,    20,
       7,    35,    16,    39,    40,    47,    14,    41,    42,    57,
      44,     0,    59,    47,    61,    63,   108,   126,   117,    63,
      57,   141,     9,    56,    61,    58,    98,    60,   120,   121,
     102,    15,    56,   157,   167,    71,    62,    57,   137,    73,
      16,    47,    63,    50,     7,    90,   122,   139,   123,   168,
      17,    18,    19,    64,    65,   130,    60,    68,    69,   192,
      61,   170,    96,    64,    98,    58,    77,    64,   102,   141,
       5,   204,     7,     8,   125,   131,   175,   127,   134,   199,
       7,   131,   138,    27,   134,    19,    41,   129,   138,    30,
      25,   127,   167,   213,    32,   129,    28,   196,   109,     1,
       5,   173,     7,     8,     9,   161,   162,   141,   164,    31,
      63,   187,   162,   189,    49,    50,    93,   192,    48,   205,
      25,   123,   178,     9,   103,    65,   202,   199,   178,   204,
       5,    -1,    84,    19,   168,   211,   168,    42,     5,   173,
      26,   213,   164,    29,    49,    50,    21,    22,    23,    24,
      25,    56,    38,    39,   152,    22,    23,    24,    25,    52,
      53,    54,    55,   151,   187,   199,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    49,    50,    51,    -1,   213
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    14,    66,    68,    69,     0,    63,   108,     9,   125,
      15,    70,    72,    73,    56,   123,    62,    67,    16,    82,
     101,    74,   125,    57,    71,   124,   125,    93,    71,    83,
     108,    47,    75,    61,   124,   127,    17,    18,    19,    94,
      95,    96,    97,   104,   105,    64,   102,   108,   125,     5,
       7,     8,    25,    49,    50,    76,    77,    78,    79,    80,
      81,   125,   108,   108,   125,   125,    26,    29,    38,    39,
     104,   107,   109,   110,   114,   118,   122,   125,    21,    22,
      23,    24,    79,    84,    85,    87,    88,    89,    90,    71,
      75,    78,    78,    72,   103,    98,   123,    98,   123,   123,
      20,   106,   108,   125,    42,    50,    76,   118,   123,   125,
     128,   129,   130,   131,   132,   133,    60,   113,    58,   119,
     120,   123,   120,   102,    76,    82,    71,    99,   100,   101,
     102,   117,   118,   125,   126,   128,   109,   113,   126,   123,
      27,   115,    43,    44,    45,    46,    47,    48,    49,    50,
      51,   134,   136,    52,    53,    54,    55,   135,   131,   131,
     128,   126,   126,    78,    91,    84,   104,   102,   108,   124,
      71,    87,   124,   127,   124,   127,   128,   124,   126,   109,
     130,   129,   131,    59,   121,   124,    41,    92,   121,   127,
      87,   100,   102,   118,   128,    30,   111,   124,    28,   116,
      50,    78,   133,    32,    86,    78,    87,   128,   109,    78,
      87,    92,    31,   112,     1,    78,   109
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    65,    66,    67,    68,    68,    68,    69,    70,    71,
      71,    72,    72,    73,    74,    74,    75,    76,    76,    76,
      76,    76,    77,    78,    79,    80,    81,    82,    82,    83,
      83,    84,    84,    85,    86,    87,    87,    87,    87,    88,
      79,    89,    90,    91,    91,    91,    92,    93,    93,    94,
      95,    95,    96,    97,    98,    98,    99,    99,   100,   100,
     101,   102,   103,   104,   104,   105,   106,   107,   107,   108,
     109,   109,   109,   109,   109,   109,   109,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   117,   118,   119,   119,
     120,   121,   122,   122,   123,   124,   125,   126,   126,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     131,   131,   131,   132,   133,   134,   134,   134,   135,   135,
     135,   135,   136,   136,   136,   136,   136,   136
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     4,     1,     5,     2,     4,     1,     4,     3,
       1,     3,     0,     1,     5,     3,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     3,     5,
       3,     1,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     3,     5,     1,     3,     0,     3,
       3,     5,     1,     1,     0,     3,     3,     1,     4,     3,
       1,     1,     3,     0,     3,     1,     1,     3,     1,     1,
       3,     1,     1,     6,     4,     8,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     2,     0,     3,
       1,     1,     1,     4,     1,     1,     1,     3,     1,     1,
       3,     1,     3,     1,     3,     1,     0,     1,     4,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1
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
       0,    84,    84,   101,   109,   121,   124,   131,   136,   155,
     166,   178,   186,   191,   197,   217,   241,   247,   248,   249,
     250,   251,   254,   256,   261,   266,   271,   276,   277,   289,
     310,   332,   335,   341,   346,   352,   353,   354,   355,   358,
     363,   368,   373,   379,   384,   389,   399,   404,   419,   424,
     437,   454,   472,   477,   482,   483,   498,   510,   524,   536,
     549,   555,   560,   577,   578,   595,   600,   606,   622,   634,
     639,   640,   641,   642,   643,   644,   645,   646,   649,   654,
     659,   664,   668,   673,   678,   684,   699,   712,   722,   723,
     736,   740,   745,   748,   756,   760,   764,   770,   785,   798,
     803,   806,   810,   811,   814,   817,   819,   820,   823,   826,
     829,   832,   835,   839,   843,   847,   850,   853,   858,   861,
     864,   867,   871,   874,   877,   880,   883,   886
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
#line 2907 "yacc_bison.h" // lalr1.cc:1167
#line 889 "parser.y" // lalr1.cc:1168

