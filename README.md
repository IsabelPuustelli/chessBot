A complete and functional chess bot made and runs in Visual Studio.

The bot asks which side the player wishes to play on. After that moves are simply made by inputting from which coordinates a piece is wished to be moved and to which
coordinates a piece is wished to be moved (eg. d2d4 is queen opening). The only exeption is o-o which is kingside castle and o-o-o which is the queenside castle.

The bot uses a minmax algorithm with paramaters that focus from most important to least important on: having more pieces than to opponent, having control of the center,
having knights on columns f and c as early as possible and putting the towers onto clear lines.

Known issues:
- Castling sometimes has the effect where the bot thinks the king is still in its original position.
