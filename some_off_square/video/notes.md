# Some Off Square

## Intro
Hi, I'm Luca, and I'd like to share my solution for the February 2024 Jane Street quant puzzle.
To preface this, I have no advanced math background, and all I did to come up with this was
thinking really hard and asking my math professor for help.

## The Problem
The problem is, we have some square of arbitrary size. We sample two points from the inside of that  <-- Fade in the circle
square, with each possible point having equal probability of being chosen. A circle is drawn from       Spawn points
these two points. In some cases, this circle will be completely contained by the square. In others,
a part of this circle will extend past the square's boundary. In this case, we say the circle is
"off" the square. What is the probability that, for a random pair of points, some of the circle
is off the square?

## Simplify the Problem
To simplify the problem, we'll start with a circle of fixed size. If this were the only circle we
had to consider, how would we solve this?

## Figuring out the Probability
An intuitive place to start would be to first find the number of ways the circle can be
off the square, and divide that by the total number of ways to place the circle. This would
represent the probability of the circle being off the square. Similarly, we could calculate
the complement of that value, 1 - the probability of not being in the square (being in the square).
To me, it sounds easier to consider the probability of being in the square. To find cases where the
circle is off the square, not only must the circle be off the square, but the points must also be
on the square. On the other hand, for a circle in the square, it is guaranteed that the points are
already inside the square. Let's start with the second option, which is to calculate the
probability of the circle being in the square.

## Numerical Representation of Circle
Before we go any further, let's give names to some of the important quantities in our situation.
Let's call the diameter of the circle d. The x-distance between the points can be w (for width),
and the y-distance h (for height). Lastly, the square will have side length L. 

## Solve for Ways to Place Circle in Square
Now, let's try to write an expression for the values we're trying to find. What are the number of
ways to put this circle in the square? Well, if we put this circle in the bottom-left corner, the
amount of wiggle room we have in the y-direction is given by (L - d). Similarly, the amount of wiggle
room we have in the x-direction is also (L - d). So, the total area of wiggle room that we have is
(L - d) ^ 2, which represents the total number of ways we can place this circle in the square.

## Solve for Total Ways to Place Circle 
What about the total number of ways to place the circle? We can take a similar approach. Let's put
the circle as far down and left as we can. Using the same method as last time, we get the relevant
area from the expression (L - x)(L - y).

## Put it all Together (For the simplified example)
So, for this circle, the probability of being off the square is:

                      (L - d) ^ 2
                1 - ----------------
                     (L - w)(L - h)

## How to generalize?
Now, how can we use this formula to generalize to all the possible circles? We can integrate over
some domain, where the domain is restricted by some constraints. To simplify this integral, let's
do 2 things. First, we'll use the Pythagorean Theorem to substitute
                    __________
                   /  2    2 
                 \/  w  + h    -> d

Second, we'll substitute 1 for L. It should be intuitively clear that the choice of what to make L
really doesn't matter as long as it's consistent. Our final answer will be the same for any L we
pick.

Now that we have a function of 2 variables, let's try to define our bounds of integration. Consider
how far our w and h can vary. The closest the two points can be is if they are right on top of each  <-- Put points in middle of circle,
other, and the farthest they can be is at opposite corners. Thus, our bounds of integration for          and have a "triangle" showing w
both are 0 to 1.                                                                                         and h. (Also put red flags on screen)

## Solve the integral
To solve this integral, we convert to polar coordinates, and get a final answer of ____. To verify
that this answer is correct, we can run a simulator, picking random points, and recording the
number of "off" squares we get. The proportion of "off" squares we get will approach...

wait *incoherent mumbling*

This...
This wasn't supposed to happen.

## Houston, we have a problem
We're actually undercounting the number of off squares. What did we do wrong?
Let's consider the behavior of our function at the endpoints of our integral. At x = 0 and y = 1,
we know from looking at it that there should be no "wiggle room" to contain the circle. The circle   <-- Compare d to L
itself is the same size as the square, so we don't get any wiggle room. But what happens when x
increases? We get a circle that is actually bigger than the square, so we definitely shouldn't have
any wiggle room...ohhhhhhh. Our function actually breaks when the circle becomes bigger than the
square. 

## Houston, we have a solution
To fix this, we can actually just stop early. If we're counting ways to place a circle
inside a square, we only need to consider circles that are smaller than the square. To find the
values we do need to check, we set up the following inequality and solve. We get the expression

                         _________
                        /      2
                 w <  \/  1 - h
                   -

## Final Answer
Now, when we plug into our integral, we should get a different answer.
1 - pi/6. How beautiful.

## 5pi/6
Now, funny story, when I submitted this problem, I tried to be smart and simplify my answer. I
turned pi/6 to 5pi/6 and sumbitted it. About an hour later, my friend asked me, "5pi/6??? That's
not even a probability!" So, realizing my mistake, I resumbitted, begging the website admin for
forgiveness. Thankfully, so many other people made this mistake, they included a note about it in
the solution, and forgave the people like me who made this silly error.

## Conclusion
I did get to the right answer, but if you think I did something wrong, please let me know with a
comment. Also, if want to share a different solution, feel free to reach out. See you next month,
after I solve the puzzle for March.
