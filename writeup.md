CS247 Plan of Attack - Due Date 3
Yash Mulki, Wolf Van Dierdonck, Matt Zhang

Introduction

We present….Chessé. While on the surface it may appear to be a standard game of chess, Chessé leverages the decorator 
pattern to enable a powerful, highly configurable and composable rule system that can radically change program 
behaviour at runtime. This enables us to do things like add rules to pieces to convert our game of chess into a game 
of checkers! Chessé also comes with advanced features including the ability to find and visualize valid moves for a 
particular piece, a sophisticated minimax based chess computer, the ability to undo and redo moves, the ability to 
view game history, and more. 

Overview of Implementation: As discussed in the plan submitted on Due Date 2, our program is broadly subdivided into 
4 main components: Game Core, Dynamic Rules, Graphics, and Chess Computer.

Core: The core module contains most of the fundamental logic that powers our chess game. The main classes in this 
module are Chess, Game, GameState & Board. Chess manages creating a new game and performing custom configuration. 
Game manages an ongoing game, prompts players (whether human or computer) for their next move and manages outputs 
(ex. Visuals, text). GameState stores the Board, and implements the vast majority of state related functions – 
checking if squares are empty, whether a piece is in check, whether a piece is owned by a particular player, etc… It 
also stores the function that executes a move as well as helper functions to validate whether a move is valid or not. 
Board is a wrapper for the underlying array that stores the board, and provides some convenience methods to simplify 
access to information about the pieces on the board. We also implement key methods such as check detection – which 
works by making a move, checking to see if the check conditions are violated by calculating the squares that the 
enemy’s pieces can attack, and then rolling back the change and reporting the move as valid or invalid based on the 
result. 

Dynamic Rules: A key element of our design is the dynamic rules component. While conventional chess systems create 
special rules for each of the 8 types of pieces in chess, our system represents these pieces as a collection of rules 
that enable behaviour. For example, we have a Castling rule that enables a piece to castle, a MoveX rule that enables 
a piece to move along the X axis, and a variety of other such rules that we compose to get different behaviour. Each 
of the fundamental chess pieces can be expressed as compositions of rules, and it is easy to build new custom pieces 
that build upon or modify the behaviour of existing chess pieces. The implementation for this system is discussed 
throughout this document and the relevant source code can be found under the Moveable folder. Construction of the 
standard pieces from the rules can be found in the PieceFactory file. We use the decorator pattern extensively to 
enable this configurable behaviour – rules can be applied on top of rules by simply creating a new instance of a rule 
that holds a reference to the underlying rule/object. This system also means that our chess computers are only 
reliant on the moves the rule sets deem to be valid. This means that they make no assumptions about the structure of 
chess themselves, and could be used in any game that uses this board with similar rules (ex. checkers).

Graphics: To enable visualization, we build upon the provided SDL wrapper (integrating it with Screen) and made key 
changes and improvements to support drawing images, text, etc… We have an output class that is subclassed by 
Visualizer, which takes in chess game states and moves from the active game. When it receives a new update, it 
considers all the squares involved in the move and updates only those ones to maximize drawing efficiency by 
minimizing the number of changes to the visual display. We also implemented support for visualizing possible moves – 
the game displays a green circle on all the spots that a particular piece can move to, much as an online chess game 
like Chess.com would. Our design involves three tiers of responsibility to decouple graphics tasks. Visualizer 
handles determining which parts of the board (logically, not pixel-wise) require updating, and manages interactions 
with game state. ChessDrawing handles high level drawing tasks (ex. Drawing a checkerboard pattern, drawing the 
correct piece, etc…). Finally, Screen handles the primitive drawing tasks – writing text, drawing images, drawing 
rectangles, applying colors, etc….

Chess Computer: We have 4 chess computers, all of which are subclasses of the Player class, which serves as the 
interface between either human or computer players and the game itself. Our computers rely on finding all possible 
moves via the methods provided by the GameState class for each of the pieces in the game. Our more basic computers 
(Computer1, Computer2, Computer3) rely on taking these moves (and in the case of 2 and 3, calculating preferred moves 
that can check, avoid capture, capture pieces, etc…) and using a uniform distribution paired with a mersenne twister 
random integer engine to generate random or semi-random behaviour amongst the filtered options. Our most 
sophisticated computer is Computer4, which is centered around a minmax algorithm that attempts to maximize the value 
of a board position. Board positions are evaluated using handcrafted position and piece weights from the PeSTO 
evaluation function used by the RofChade chess engine. We also apply an alpha-beta pruning technique to [INSERT 
EXPLANATION HERE WOLF]

Updated UML and Discussion of Changes

The changes we made to our original UML diagram are minimal and highlighted in the diagram. They generally occurred 
because our implementation gave us more insight into the design of a particular component:

In terms of the schedule, we generally followed our predetermined schedule that we submitted in the plan on due date 
2. The graphics component took less time than expected, and the decorator/dynamic rules component took more than 
expected, but these ended up compensating for each other. 

Design Patterns & Challenges

Decorator: We make extensive use of the decorator pattern, and it serves as a core part of our system design. 
Traditionally, chess games are rigid and encode specific rules for each of the 8 different types of chess pieces. By 
contrast, we leverage the decorator pattern to represent pieces as simply collections of rules that can be stacked, 
composed and combined. For example, a Rook is simply a chess piece that has the MoveX and MoveY rules (which allow it 
to move up and down, left and right), and behaviours like Castling are expressed via the application of a Castling 
rule (Castle.cc). This is best demonstrated by PieceFactory.cc, which constructs the basic chess types by composing 
various rules. This structure allows us to avoid duplication (ex. Queens also have the MoveX and MoveY rules), and 
create new pieces by combining behaviours. The decorator pattern serves as the perfect solution to the problem of 
designing this system, as it allows us to compose rules effectively. The use of this pattern can be seen in the 
source files under the Moveable folder. We have a Moveable class, which serves as our abstract base class for rules/
pieces. Piece inherits from Moveable and represents a concrete chess piece. Then, Decorator and the various rules 
that inherit from it (ex. MoveX) apply rules onto pieces and enable more complex behaviours like composing rules. 

Decoupling: A key goal in the design and development of this project was decoupling components of the program and 
clearly defining the responsibilities of each component. Not only does this approach yield a more logical and 
readable codebase, but it also makes it easier to collaborate as components can be worked on in isolation. This is 
discussed in the next section in more detail, and some examples are provided. This strategy informed the design of 
our UML diagram and class structure, aiming to decouple interfaces (how two components interact) from how they 
actually accomplish their task (the implementation).

Resilience to Change

Our design is architected with future expansion and change in mind, and hence incorporates a variety of key features 
to accommodate it. 
Firstly, we make no assumptions in the core game logic about the size of the chess board. If we were to extend the 
game to any square sized chess board, we’d be able to accommodate it (barring graphics, which would require changes).
Secondly, our program makes minimal assumptions about the game of chess itself, besides the basic minimum. We 
conceptualize and implement the various chess pieces as essentially a set of rules, as opposed to some distinct item. 
For example, our conception of a Rook is simply a board piece that has the MoveX and MoveY rules applied to it, which 
allows it to move along the two axes. Obviously, we have special rulesets to supplement the unique features it 
provides (ex. castling). These rules are also used by the Queen piece. Due to this dynamic and configurable 
structure, rules can be reused to create new behaviours for pieces. This also leaves open the door to defining new 
rules in the future to specify new behaviours for chess pieces, or even the inclusion of new pieces. As a 
demonstration of the power of our rule system, we are able to (as will have been demonstrated) convert the game to a 
basic version of checkers at runtime, simply by applying a new rule on pieces. These rules can also interact with 
each other (ie. we can have a rule add to the possible moves that other rules apply, or limit these moves, etc..) and 
can be ordered to produce different interactions when applied to a piece. This can be seen in action in PieceFactory, 
where we construct our chess types by composing rules.
Thirdly, we’ve decoupled the roles of different components from their actual functionality whenever possible – ex. 
Computers are just players that happen to have an algorithm to determine their next move. This structure means that 
if we wanted to add new player types (ex. An online player) or new computers, it would be a simple task that would 
not require significant changes to our existing structure (change would be isolated to the new component). Similarly, 
our outputs are also separated into role and specific implementation – we have a common class Output that takes in a 
state and a move at each step. This class is subclassed by Visualizer and TextDisplay which covers their respective 
output modalities. This makes it simply to add new output methods – for example, we could support output to a braille 
display by creating a new subclass and interfacing with hardware.
We also make minimal assumptions about the number and nature of players on the board. Instead of storing the current 
player as black or white, we instead utilize a PlayerColour enum. On move completion, instead of toggling player, we 
simply move to the next player defined in the enumeration, which means we can add support for more players by 
extending the enumeration and defining the order of players in our playerColor.cc file.
Finally, the game (ie. the inputs, game creation, etc…) and the game state (board, current player, etc..) are 
decoupled, which makes the codebase significantly more resilient to change as we can quickly change one in isolation 
of the other. For example, we could enable support for exporting and importing GameStates with just a few lines of 
code. 

Project Specific Questions

Q: Chess programs usually come with a book of standard opening move sequences, which list accepted opening moves and 
responses to opponents’ moves, for the first dozen or so moves of the game. Although you are not required to support 
this, discuss how you would implement a book of standard openings if required.
A: We’d implement a new subclass of Human called OpeningSequence, which would override the doNextMove(const 
GameState &) method and, while the opening sequence is not yet exhausted, would provide the next move from the 
standard moves. The sequence itself could be stored either within the class, in an array, or be stored in a text file 
and loaded using an ifstream by the OpeningSequence class. Once the move sequence has been exhausted, the subclass 
can just call doNextMove for the superclass (Human), which would prompt the user for input. We’d then just substitute 
an object of type OpeningSequence for one of type Human while initializing the game. The OpeningSequence class could 
prompt the user to select which standard opening sequence to use when it is first prompted for moves by the game.
How it differs: This is the same strategy we discussed in our plan on due date 2, with some modifications. Instead of 
storing a reference to a human and forwarding the game’s requests for input once the move sequence is exhausted, we 
now instead override the relevant methods of the human class and provide input while the move sequence has moves to 
be played. We’ve also added some detail based on our final implementation.
Q: How would you implement a feature that would allow a player to undo his/her last move? What about an unlimited 
number of undos?
A: TBD, pending potential optimization
How it differs: 

 Variations on chess abound. For example, four-handed chess is a variant that is played by four players (search for 
 it!). Outline the changes that would be necessary to make your program into a four-handed chess game.
A: Currently, our design does not specify the number of players, instead using an enum to encode the current player.  
In addition, we store our players in a vector instead of as just two players. This means that it’d be pretty easy 
from an input and state management perspective to enable 4 handed chess. The biggest challenge would be the board, as 
while we do not hardcode an 8x8 board we still make the assumption that the board is square. We’d have to adapt board 
configuration to allow widths to be specified row by row to allow for the more complex board design in 4 handed 
chess. Additionally, we would have to change the Output (both text and graphics) to enable support for displaying 
4-player boards.
How it differs: This is the same strategy outlined in the initial plan with some updated details on how we store the 
current player (an enum instead of an int)
Extra Credit Features

We implemented our entire program using no manual memory management (except for some SDL functions, as the SDL 
library provides functions to handle surfaces, etc… and clean up its own resources). We never stored raw pointers 
directly (except between SDL API calls) and used unique and shared pointers for all other uses. We never use the 
keyword delete (in reference to memory management - there are some deletes used to mark constructors as deleted). 

Our decorator based dynamic rule systems significantly adds to the behaviour our program can express beyond that of 
regular chess. We demonstrate this with some fun additional rules [MATT ADD THESE]. This system enables composable 
rulemaking and the ability to change up the rules of the chess game at runtime by simply adding/removing rules from 
different pieces. It also makes the game infinitely extensible, with the ability to add new rules onto existing 
pieces, or build upon existing rules to design new pieces with novel behaviour. This was extremely complex to 
implement as we needed to set up a base class, and then setup a pipeline to augment valid moves of a piece based on 
the rules applied to it (and in the particular order they were applied). This required significant architecture and  
design decisions regarding the class structure. 

As mentioned previously, the decorator pattern is instrumental in implementing our vision of dynamic piece movesets. 
We abstracted the concept of a chess piece to simply an entity on the board, or “Moveable”. At a high level, each 
Moveable has one main responsibility - to report a list of valid moves given a gamestate. To achieve this, we start 
with a trivial concrete class which returns no valid moves. We then decorate it with additional logic, from ones that 
simply allow it to move a certain number of steps along the x-axis to allowing it to forcefully move other pieces 
(castling) to allowing it to turn into another piece upon satisfying certain conditions (promotion). In addition to 
the architectual challenge when implementing these behaviors, another problem we faced is that some rulesets required 
knowledge of the possible moves of other pieces. For example, standard chess rules prohibit castling if any tile 
along its path to its final position is under attack(ie. kings cannot “castle through check”). This leads to circular 
dependencies resulting in infinite recursive stacks. For example, a situation may arise in which  piece A’s valid 
moves depended on piece B’s valid moves, which then depended on piece A’s valid moves ad infinitum. To resolve this, 
we observed that A does not need to know B’s valid moves; instead, A needed information on the tiles that B attacks. 
This is a subtle difference in all but a few cases(in particular, pinned pieces and pieces that capture differently 
from how they normally move). By making this distinction, we sidestep the circular dependency by having Moveables 
report their possible moves and the tiles they attack separately.

Another key improvement we made was supporting game history and allowing users to undo moves. Just like real chess 
games (ex. Chess.com), we support viewing a log of all the moves that have transpired since the beginning of the 
game. This allows users to retrace their steps easily, and the undo feature allows them to correct mistakes. This was 
challenging as we needed to keep track of the game state at each step, and be able to dynamically revert state, 
including the currently active user, etc… We solved this by decoupling the active game’s management from its state 
management, allowing us to swap out the state at runtime for a different state. This allows us to undo moves quickly 
(and undo any number of moves) by reverting to a previous state. This solution results in no side effects and 
perfectly moves back to the corresponding state the game was in before a move was played. This also leaves open the 
possibility to easily serialize and export a gamestate and then import and deserialize it (enabling possibilities 
like a multiplayer version of this chess game where the game state is sent to another computer over the internet). 

Another major feature is the ability to view valid moves for any piece. This makes it a lot easier for the user to 
see what they can move next. Users simply need to prompt the computer by typing in valid <piece-location> to see 
where a particular piece can be moved. In addition to enumerating the possible destination location in the terminal, 
the visualizer also displays these positions on the screen by way of small green dots on potential destination 
squares. This was challenging as we needed heuristics to efficiently get valid moves (even from a complex piece that 
involved stacks of many rules). We solved this by implementing a Moveable::getValidMoves() method where each rule 
augments it to add/remove valid moves based on the rule. This also helped the chess computers decide where they could 
play next – and this works not just for the basic chess pieces but any complex pieces that we compose with our rules.

 Our chess engines can even optimize a checkers game (where we have applied checkers rules) as they make no 
 assumptions about the underlying game and purely make decisions based on the valid moves that pieces report. 


Finally, a convenience feature we added was to quickly setup a standard chessboard by typing in “setup standard done” 
once a game was started. This makes it easier for a user to start a chess game, and made it easier for us to test.

Final Questions

Q: What lessons did this project teach you about developing software in teams? If you worked alone, what lessons did 
you learn about writing large programs?

A:  While working on this project, we learned the value of leveraging collaboration tools like git, which enabled us 
to collaborate and iterate rapidly. Another key realization was the importance of designing the project in a manner 
that’s conducive to collaborative, parallel work. By decoupling various components of the project, we were able to 
work on things in isolation that would then work together with components made by other members of the team. This 
allowed us to work rapidly and asynchronously, which allowed us to tackle multiple components simultaneously. This 
allowed us to divide co. One thing that was extremely useful was getting our core data classes setup in advance (in 
the data/ folder, contains classes like Position, Move, PieceType, etc..), so when we worked on the various 
components we had common data interchange formats that we could use to communicate.


We also learned the importance of clearly dividing up responsibilities based on relevant experience/knowledge in 
certain areas. For example,  Wolf had pre-existing knowledge about the design of chess computers, and Yash has had 
past experience working with graphics/UI. This allowed us to work as efficiently as possible by playing to our 
strengths.

Q: What would you have done differently if you had the chance to start over?

A: We’d think more about how to perform check detection in a more efficient and sophisticated way. Currently, our 
approach correctly identifies all possible situations where check is a concern in terms of valid piece moves or 
detecting stalemate/checkmate. However, it is not very efficient and hence inhibits the ability of the computer to 
calculate more moves in advance. We’d have put more effort into optimizing this algorithm.

Another thing we’d have done differently is use the SDL2 library instead of the SDL library. When we began, support 
was only available for SDL1 and our graphics component was largely completed using it, so we made the decision to 
stick with it. If we were able to start over we’d use the SDL2 library as it has more documentation available and 
also provides more higher level drawing methods (ex. Drawing lines).

One change that would have significantly simplified our development and testing process would be to create setup 
commands to configure the board with standard positions earlier. We initially relied on manually adding in pieces 
which added significant overhead to testing functionality and the chess computers. We later added a setup standard 
command that vastly simplified this process and increased iteration speed. 

We’d also improve our code management workflow – pushing straight to main on the repo resulted in a lot of merge 
conflicts, and using pull requests would have made it a less chaotic process. It would also be easier to track 
changes that should be grouped in order to revert to working states, etc…

Conclusion

We had a great time making Chessé, and enjoyed seeing how the design patterns we learned in CS247 could add new 
functionality to the game of chess, and enable us to build our dynamic, runtime-modifiable system. It was really fun 
learning more about the various quirks of chess, and the design of chess computers. 
