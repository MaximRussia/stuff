/**
12.1 Find the mistake(s) in the following code:
**/
unsigned int i;
for (i = 100; i >= 0; --i)
printf("%d\n", i);
/**
Solution:
1) 'unsigned int >= 0' is true all the time (replace by i > 0)
2) "%d\n" replace by "%u\n"
**/

/**
12.2 You are given the source to an application which crashes when it is run. After running
it ten times in a debugger, you find it never crashes in the same place. The applica-
tion is single threaded, and uses only the C standard library. What programming
errors could be causing this crash ? How would you test each one?
Solution:
1) Random numbers
2) Uninitialized Variables
3) Memory Leak / Memory Corruption
4) External Dependencies (files, servers etc.)
**/

/**
12.3 We have the following method used in a chess game: boolean canMoveTofint x, int
y). This method is part of the Piece class and returns whether or not the piece can
move to position (x, y). Explain how you would test this method.
Solution:
Write test cases (throw exeption or return false)
Extreme cases: x < 0, y < 0, x > width, y > height, empty board, full board
**/

/**
12.6 How would you test an ATM in a distributed banking system?
Solution:
The first thing to do on this question is to clarify assumptions. Ask the following ques-
tions:
• Who is going to use-the ATM? Answers might be "anyone," or it might be "blind
people," or any number of other answers.
• What are they going to use it for? Answers might be "withdrawing money,""transfer-
ring money,""checking their balance,"or many other answers.
• What tools do we have to test? Do we have access to the code, or just to the ATM?
Remember: a good tester makes sure she knows what she's testing!
Once we understand what the system looks like, we'll want to break down the problem
into different testable components.These components include:
• Logging in
• Withdrawing money
• Depositing money
• Checking balance
• Transferring money
We would probably want to use a mix of manual and automated testing.
Manual testing would involve going through the steps above, making sure to check for
all the error cases (low balance, new account, nonexistent account, and so on).
Automated testing is a bit more complex. We'll want to automate all the standard
scenarios, as shown above, and we also want to look for some very specific issues,
such as race conditions. Ideally, we would be able to set up a closed system with fake
accounts and ensure that, even if someone withdraws and deposits money rapidly from
different locations, he never gets money or loses money that he shouldn't.
Above all, we need to prioritize security and reliability. People's accounts must always be
protected, and we must make sure that money is always properly accounted for. No one
wants to unexpectedly lose money! A good tester understands the system priorities.
**/
