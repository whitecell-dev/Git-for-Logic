# ======================================================================
# NO MORE LIES TO THE RUNTIME - MULTI-LANGUAGE RULES
# CALYX Atlas Integration for Python, Go, TypeScript
# ======================================================================

# ======================================================================
# PYTHON EDITION
# ======================================================================
python_rules:
  title: "NO MORE LIES TO THE INTERPRETER: PYTHON EDITION"
  language: python
  runtime_type: "interpreted"
  version: "3.8+"
  
  type_safety:
    - rule: "NO UNTYPED FUNCTIONS"
      bad: |
        def process(data):
            return data['value']
      good: |
        from typing import Dict, Any
        def process(data: Dict[str, Any]) -> int:
            return data['value']
      rationale: "Type hints enable static analysis and Atlas generation"
    
    - rule: "NO BARE EXCEPTIONS"
      bad: |
        try:
            risky_operation()
        except:
            pass
      good: |
        try:
            risky_operation()
        except ValueError as e:
            logger.error(f"Invalid value: {e}")
            return Result.error(str(e))
      rationale: "Explicit exception types show in call graphs"
    
    - rule: "NO IMPLICIT NONE"
      bad: |
        def find_user(id: int):
            # Returns None implicitly
            pass
      good: |
        from typing import Optional
        def find_user(id: int) -> Optional[User]:
            return None  # Explicit
      rationale: "Optional is graph-addressable in Atlas"
  
  data_structures:
    - rule: "NO MUTABLE DEFAULTS"
      bad: |
        def add_item(item, items=[]):
            items.append(item)
            return items
      good: |
        from typing import List, Optional
        def add_item(item: str, items: Optional[List[str]] = None) -> List[str]:
            if items is None:
                items = []
            items.append(item)
            return items
      rationale: "Mutable defaults break purity analysis"
    
    - rule: "NO DICT[STR, ANY]"
      bad: |
        user: Dict[str, Any] = {'id': 1, 'name': 'Alice'}
      good: |
        from dataclasses import dataclass
        @dataclass
        class User:
            id: int
            name: str
        user = User(id=1, name='Alice')
      rationale: "Dataclasses are indexable in Atlas type system"
    
    - rule: "NO GLOBAL STATE"
      bad: |
        CACHE = {}
        def get_data(key):
            return CACHE.get(key)
      good: |
        class DataStore:
            def __init__(self):
                self._cache: Dict[str, Any] = {}
            def get(self, key: str) -> Optional[Any]:
                return self._cache.get(key)
      rationale: "Instance state is traceable in dependency graph"
  
  error_handling:
    - rule: "NO SILENT FAILURES"
      bad: |
        def divide(a, b):
            try:
                return a / b
            except ZeroDivisionError:
                return None
      good: |
        from typing import Union
        from enum import Enum
        
        class ErrorKind(Enum):
            DIV_ZERO = "division_by_zero"
        
        @dataclass
        class Error:
            kind: ErrorKind
            message: str
        
        def divide(a: float, b: float) -> Union[float, Error]:
            if b == 0:
                return Error(ErrorKind.DIV_ZERO, "Cannot divide by zero")
            return a / b
      rationale: "Result types are explicit in Atlas call graph"
    
    - rule: "NO BARE ASSERT"
      bad: |
        assert user is not None
        process(user)
      good: |
        if user is None:
            raise ValueError("User cannot be None")
        process(user)
      rationale: "Explicit checks show in control flow graph"
  
  module_structure:
    - rule: "NO CIRCULAR IMPORTS"
      bad: |
        # a.py
        from b import func_b
        # b.py  
        from a import func_a
      good: |
        # a.py
        from typing import TYPE_CHECKING
        if TYPE_CHECKING:
            from b import func_b
        # b.py
        # No import of a
      rationale: "Atlas requires DAG structure"
    
    - rule: "NO SIDE EFFECTS AT MODULE LEVEL"
      bad: |
        # config.py
        DATABASE = connect_to_db()  # Side effect!
      good: |
        # config.py
        def get_database() -> Database:
            return connect_to_db()
      rationale: "Import graph must be pure"
  
  performance:
    - rule: "NO LIST COMPREHENSION ABUSE"
      bad: |
        # Forces evaluation of entire list
        any([expensive(x) for x in huge_list])
      good: |
        # Generator - lazy evaluation
        any(expensive(x) for x in huge_list)
      rationale: "Generators are analyzable as stream transforms"
    
    - rule: "NO REPEATED ATTRIBUTE LOOKUP"
      bad: |
        for i in range(len(items)):
            process(items[i].data.value.field)
      good: |
        for item in items:
            field = item.data.value.field  # Cache lookup
            process(field)
      rationale: "Reduces cognitive load in hot path analysis"
  
  calyx_integration:
    atlas_metadata:
      - "Use __all__ to declare public API"
      - "Add type: ignore only with explanation comments"
      - "Document purity with @pure decorator (custom)"
    
    layer_classification:
      NEXUS: "Modules doing I/O (files, network, DB)"
      ALBEO: "Pure functions (no I/O, deterministic)"
      BRIDGE: "Data transformation (JSON, XML, Protocol Buffers)"
      FSM: "State machines (explicit state enums)"
      MNEME: "Logging, audit (write-only I/O)"
    
    forbidden_in_pure_modules:
      - "open(), requests.get(), database.query()"
      - "datetime.now(), random.random()"
      - "Global variables, class variables"
    
    validation_tools:
      - "mypy --strict"
      - "pylint --disable=C0103"
      - "bandit (security)"


# ======================================================================
# GO EDITION
# ======================================================================
go_rules:
  title: "NO MORE LIES TO THE COMPILER: GO EDITION"
  language: go
  runtime_type: "compiled"
  version: "1.18+"
  
  error_handling:
    - rule: "NO IGNORED ERRORS"
      bad: |
        result, _ := riskyOperation()
      good: |
        result, err := riskyOperation()
        if err != nil {
            return fmt.Errorf("operation failed: %w", err)
        }
      rationale: "Error returns are explicit in Atlas call graph"
    
    - rule: "NO PANIC IN LIBRARY CODE"
      bad: |
        func Process(data string) int {
            if data == "" {
                panic("empty data")
            }
            return len(data)
        }
      good: |
        func Process(data string) (int, error) {
            if data == "" {
                return 0, errors.New("empty data")
            }
            return len(data), nil
        }
      rationale: "Error returns are graph-addressable"
    
    - rule: "NO SENTINEL ERRORS WITHOUT WRAPPING"
      bad: |
        var ErrNotFound = errors.New("not found")
        return ErrNotFound
      good: |
        var ErrNotFound = errors.New("not found")
        return fmt.Errorf("user lookup: %w", ErrNotFound)
      rationale: "Error chains show in MNEME audit trail"
  
  type_safety:
    - rule: "NO EMPTY INTERFACE ABUSE"
      bad: |
        func Process(data interface{}) error {
            // Type assertion hell
            str, ok := data.(string)
            if !ok {
                return errors.New("not a string")
            }
            return nil
        }
      good: |
        func Process(data string) error {
            // Type known at compile time
            return nil
        }
      rationale: "Concrete types are indexable in Atlas"
    
    - rule: "NO UNTYPED NIL"
      bad: |
        var user *User
        if condition {
            user = &User{ID: 1}
        }
        return user  // Might be nil
      good: |
        type Optional[T any] struct {
            value T
            valid bool
        }
        
        func (o Optional[T]) Get() (T, bool) {
            return o.value, o.valid
        }
        
        var user Optional[User]
        if condition {
            user = Optional[User]{value: User{ID: 1}, valid: true}
        }
        return user
      rationale: "Optional is explicit in type system"
    
    - rule: "NO MAP WITHOUT OK CHECK"
      bad: |
        value := myMap[key]
        process(value)  // Zero value if not found
      good: |
        value, ok := myMap[key]
        if !ok {
            return errors.New("key not found")
        }
        process(value)
      rationale: "Map access errors are control flow nodes"
  
  concurrency:
    - rule: "NO GOROUTINE LEAKS"
      bad: |
        func Process() {
            go func() {
                // Never returns, no cancellation
                for {
                    work()
                }
            }()
        }
      good: |
        func Process(ctx context.Context) {
            go func() {
                for {
                    select {
                    case <-ctx.Done():
                        return
                    default:
                        work()
                    }
                }
            }()
        }
      rationale: "Goroutines are resources tracked in Atlas"
    
    - rule: "NO SHARED MEMORY WITHOUT MUTEX"
      bad: |
        var counter int
        go func() { counter++ }()
        go func() { counter++ }()
      good: |
        var (
            counter int
            mu      sync.Mutex
        )
        go func() {
            mu.Lock()
            counter++
            mu.Unlock()
        }()
      rationale: "Mutex boundaries are NEXUS layer nodes"
    
    - rule: "NO CHANNEL WITHOUT CLOSE"
      bad: |
        ch := make(chan int)
        go func() {
            for i := 0; i < 10; i++ {
                ch <- i
            }
            // Never closes
        }()
      good: |
        ch := make(chan int)
        go func() {
            defer close(ch)
            for i := 0; i < 10; i++ {
                ch <- i
            }
        }()
      rationale: "Channel lifecycle is resource graph edge"
  
  structure:
    - rule: "NO INIT() FOR SIDE EFFECTS"
      bad: |
        func init() {
            database = connectToDB()  // Side effect
        }
      good: |
        var database *DB
        
        func InitDatabase() error {
            var err error
            database, err = connectToDB()
            return err
        }
      rationale: "Explicit initialization is traceable"
    
    - rule: "NO PACKAGE GLOBAL MUTABLE STATE"
      bad: |
        var Cache = make(map[string]string)
      good: |
        type CacheManager struct {
            cache map[string]string
            mu    sync.RWMutex
        }
        
        func NewCacheManager() *CacheManager {
            return &CacheManager{
                cache: make(map[string]string),
            }
        }
      rationale: "Instance state is module-scoped in Atlas"
  
  interfaces:
    - rule: "NO INTERFACE POLLUTION"
      bad: |
        // Defining interface before implementation exists
        type UserService interface {
            GetUser(id int) (*User, error)
            CreateUser(u *User) error
            UpdateUser(u *User) error
            DeleteUser(id int) error
            ListUsers() ([]*User, error)
        }
      good: |
        // Define interface at usage site
        type UserGetter interface {
            GetUser(id int) (*User, error)
        }
        
        func ProcessUser(getter UserGetter) {
            user, _ := getter.GetUser(1)
            // ...
        }
      rationale: "Interfaces are dependency edges in Atlas"
  
  calyx_integration:
    atlas_metadata:
      - "Use go:generate for code generation metadata"
      - "Document purity with //go:pure comment (custom)"
      - "Embed build tags in Atlas: // +build linux"
    
    layer_classification:
      NEXUS: "Packages with I/O (os, net, database/sql)"
      ALBEO: "Pure packages (math, strings, encoding)"
      BRIDGE: "Data transformation (encoding/json, protobuf)"
      FSM: "State machines (explicit state types)"
      MNEME: "Logging (log, zerolog)"
    
    forbidden_in_pure_packages:
      - "import \"os\", import \"net/http\""
      - "time.Now(), rand.Intn()"
      - "Package-level vars (except const)"
    
    validation_tools:
      - "go vet ./..."
      - "staticcheck ./..."
      - "golangci-lint run --enable-all"


# ======================================================================
# TYPESCRIPT EDITION
# ======================================================================
typescript_rules:
  title: "NO MORE LIES TO THE RUNTIME: TYPESCRIPT EDITION"
  language: typescript
  runtime_type: "transpiled"
  version: "5.0+"
  
  type_safety:
    - rule: "NO ANY TYPE"
      bad: |
        function process(data: any): any {
            return data.value;
        }
      good: |
        interface DataInput {
            value: number;
        }
        function process(data: DataInput): number {
            return data.value;
        }
      rationale: "any breaks Atlas type inference"
    
    - rule: "NO IMPLICIT ANY"
      bad: |
        const items = [1, 2, 3];
        const first = items.find(x => x > 5);  // Type is number | undefined
        console.log(first.toString());  // Runtime error!
      good: |
        const items: number[] = [1, 2, 3];
        const first = items.find(x => x > 5);
        if (first !== undefined) {
            console.log(first.toString());
        }
      rationale: "Undefined checks are control flow nodes"
    
    - rule: "NO TYPE ASSERTIONS WITHOUT GUARDS"
      bad: |
        const user = data as User;
        process(user.name);
      good: |
        function isUser(data: unknown): data is User {
            return (
                typeof data === 'object' &&
                data !== null &&
                'name' in data &&
                typeof (data as any).name === 'string'
            );
        }
        
        if (isUser(data)) {
            process(data.name);
        }
      rationale: "Type guards are validation nodes in Atlas"
    
    - rule: "NO NON-NULL ASSERTION"
      bad: |
        const value = maybeValue!;
        process(value);
      good: |
        if (maybeValue === null || maybeValue === undefined) {
            throw new Error("Value is required");
        }
        process(maybeValue);
      rationale: "! operator hides null checks from Atlas"
  
  error_handling:
    - rule: "NO THROWING PRIMITIVES"
      bad: |
        throw "Error occurred";
        throw 404;
      good: |
        class AppError extends Error {
            constructor(
                message: string,
                public readonly code: string,
                public readonly context?: Record<string, unknown>
            ) {
                super(message);
                this.name = 'AppError';
            }
        }
        
        throw new AppError("Not found", "ERR_NOT_FOUND", { userId: 123 });
      rationale: "Structured errors are indexable in MNEME"
    
    - rule: "NO TRY WITHOUT TYPED CATCH"
      bad: |
        try {
            await riskyOperation();
        } catch (e) {
            console.log(e);  // e is any
        }
      good: |
        try {
            await riskyOperation();
        } catch (e) {
            if (e instanceof AppError) {
                logger.error(e.message, { code: e.code });
            } else if (e instanceof Error) {
                logger.error(e.message);
            } else {
                logger.error('Unknown error', { error: e });
            }
        }
      rationale: "Typed catch blocks are graph nodes"
    
    - rule: "NO PROMISE WITHOUT ERROR HANDLING"
      bad: |
        fetchData().then(data => process(data));
      good: |
        fetchData()
            .then(data => process(data))
            .catch(err => handleError(err));
        
        // Or better: async/await
        try {
            const data = await fetchData();
            process(data);
        } catch (err) {
            handleError(err);
        }
      rationale: "Error paths are explicit in Atlas"
  
  async_patterns:
    - rule: "NO FLOATING PROMISES"
      bad: |
        async function run() {
            doAsync();  // Promise not awaited
        }
      good: |
        async function run() {
            await doAsync();
            // Or explicitly:
            void doAsync();  // Intentional fire-and-forget
        }
      rationale: "Awaited promises are async edges in Atlas"
    
    - rule: "NO PROMISE CONSTRUCTOR ANTIPATTERN"
      bad: |
        function fetchUser(id: number): Promise<User> {
            return new Promise((resolve, reject) => {
                getUserFromDB(id)
                    .then(user => resolve(user))
                    .catch(err => reject(err));
            });
        }
      good: |
        async function fetchUser(id: number): Promise<User> {
            return await getUserFromDB(id);
        }
      rationale: "Unnecessary Promise wrappers obscure call graph"
  
  structure:
    - rule: "NO DEFAULT EXPORTS"
      bad: |
        export default class UserService { }
      good: |
        export class UserService { }
      rationale: "Named exports are graph-addressable"
    
    - rule: "NO BARREL FILES WITHOUT RE-EXPORT"
      bad: |
        // index.ts
        export * from './moduleA';
        export * from './moduleB';
      good: |
        // index.ts
        export { SpecificClassA, SpecificFunctionA } from './moduleA';
        export { SpecificClassB } from './moduleB';
      rationale: "Explicit re-exports show in dependency graph"
    
    - rule: "NO NAMESPACE POLLUTION"
      bad: |
        namespace Utils {
            export function helper1() { }
            export function helper2() { }
        }
      good: |
        export function utilHelper1() { }
        export function utilHelper2() { }
      rationale: "Namespaces are legacy, use modules"
  
  react_specific:
    - rule: "NO INLINE FUNCTION PROPS"
      bad: |
        <Button onClick={() => handleClick(id)} />
      good: |
        const handleButtonClick = useCallback(() => {
            handleClick(id);
        }, [id]);
        
        <Button onClick={handleButtonClick} />
      rationale: "Callback identity is tracked in Atlas"
    
    - rule: "NO UNTYPED PROPS"
      bad: |
        function Component({ data }) {
            return <div>{data.name}</div>;
        }
      good: |
        interface ComponentProps {
            data: {
                name: string;
            };
        }
        
        function Component({ data }: ComponentProps) {
            return <div>{data.name}</div>;
        }
      rationale: "Component props are interface boundaries"
    
    - rule: "NO USEEFFECT WITHOUT DEPS"
      bad: |
        useEffect(() => {
            fetchData();
        });  // Runs on every render
      good: |
        useEffect(() => {
            fetchData();
        }, []);  // Explicit empty deps = mount only
      rationale: "Effect dependencies are data flow edges"
  
  calyx_integration:
    atlas_metadata:
      - "Use @pure JSDoc tag for pure functions"
      - "Document side effects with @sideEffect tag"
      - "Mark frozen APIs with @frozen tag"
    
    tsconfig_requirements:
      strict: true
      noImplicitAny: true
      strictNullChecks: true
      strictFunctionTypes: true
      noUnusedLocals: true
      noUnusedParameters: true
      noImplicitReturns: true
      noFallthroughCasesInSwitch: true
    
    layer_classification:
      NEXUS: "Modules with fetch, fs, process"
      ALBEO: "Pure functions (lodash, ramda style)"
      BRIDGE: "Data transformation (JSON, XML, GraphQL)"
      FSM: "React components with state machines"
      MNEME: "Logging (winston, pino)"
    
    forbidden_in_pure_modules:
      - "fetch(), axios.get()"
      - "Date.now(), Math.random()"
      - "localStorage, sessionStorage"
      - "console.log() in production"
    
    validation_tools:
      - "tsc --noEmit"
      - "eslint --max-warnings 0"
      - "prettier --check"


# ======================================================================
# CROSS-LANGUAGE PRINCIPLES
# ======================================================================
universal_principles:
  title: "UNIVERSAL NO MORE LIES PRINCIPLES"
  
  cognitive_load:
    - "Functions < 50 lines (cognitive bubble limit)"
    - "Modules < 500 lines (single attention window)"
    - "Nesting depth < 4 (avoid pyramid of doom)"
    - "Function parameters < 5 (interface cardinality limit)"
  
  purity:
    - "Pure functions return same output for same input"
    - "Pure functions have no side effects"
    - "Pure functions don't depend on global state"
    - "Mark impure functions with explicit annotations"
  
  error_as_data:
    - "Errors are return values, not exceptions (when possible)"
    - "Error types are part of function signature"
    - "Error chains show causal relationships"
    - "Logs are write-only (never read in same process)"
  
  explicit_state:
    - "All state is owned by a single module"
    - "State transitions are explicit functions"
    - "Shared state requires synchronization primitives"
    - "Immutability by default, mutation by annotation"
  
  dependency_hygiene:
    - "Dependency graph is a DAG (no cycles)"
    - "Core modules have zero external dependencies"
    - "Interface modules depend only on types"
    - "Test code never imported by production code"
  
  atlas_integration:
    module_metadata:
      - "Every module declares its layer (NEXUS/ALBEO/BRIDGE/FSM/MNEME)"
      - "Every module declares its purity level"
      - "Every module lists its I/O operations"
      - "Every module lists its frozen interfaces"
    
    validation_pipeline:
      - "Static analysis: type checking"
      - "Linting: style and safety rules"
      - "Atlas generation: architectural extraction"
      - "Constraint checking: layer violations"
    
    llm_optimization:
      - "Use semantic types (not primitives)"
      - "Use explicit error types (not exceptions)"
      - "Use named constants (not magic numbers)"
      - "Use structured logging (not print)"


# ======================================================================
# ATLAS INTEGRATION CHECKLIST
# ======================================================================
atlas_integration_checklist:
  before_generation:
    - "All functions have type annotations"
    - "All error paths are explicit"
    - "All side effects are documented"
    - "All dependencies are declared"
  
  during_generation:
    - "Parser extracts type signatures"
    - "Analyzer builds call graph"
    - "Classifier assigns layers"
    - "Validator checks constraints"
  
  after_generation:
    - "Atlas validates against schema"
    - "Conflicts are resolved"
    - "Confidence scores assigned"
    - "LLM consumption format generated"
  
  llm_query_patterns:
    - "What are the side effects of module X?"
    - "Which functions violate purity in layer ALBEO?"
    - "Show me the call chain from A to B"
    - "Which modules have circular dependencies?"
    - "What's the cognitive load of function F?"

# templates/lua_no_more_lies.yaml  
title: "NO MORE LIES TO THE RUNTIME: LUA EDITION"
language: lua
runtime_type: "interpreted"
rules:
  globals:
    - "NO GLOBAL VARIABLES: Everything in named tables"
    - "NO IMPLICIT MODIFICATION: Use metatables for protection"
    - "NO SIDE EFFECTS IN MODULES: Keep modules pure"
  tables:
    - "NO WEAK TYPING: Use table.type fields"
    - "NO MIXED TABLES: Arrays vs maps, not both"
    - "NO INLINE CONSTRUCTION: Use factory functions"
  errors:
    - "NO SILENT FAILURES: Always return {ok=, error=} pattern"
    - "NO RAW THROW: Use structured error objects"
    - "NO NIL CHAINS: Use safe navigation patterns"
  performance:
    - "NO GLOBAL LOOKUPS: Cache locals"
    - "NO TABLE REALLOCATION: Pre-size tables"
    - "NO FUNCTION CREATION IN LOOPS: Hoist function definitions"

