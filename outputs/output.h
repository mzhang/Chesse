#ifndef OUTPUT_H_
#define OUTPUT_H_

class GameState;
class Position;
class Move;

class Output 
{
    virtual void doUpdate(const GameState &, const Move &) = 0;
protected:
    bool isBlackTile(const Position &);
public:
    void update(const GameState &, const Move &);
};

#endif
