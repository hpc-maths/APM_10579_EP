---
title: "MAP586 project"
subtitle: "1D PDE solver"
# author: "L. Gouarin and J. Mabille"
date: 2022-01-27
---

## Introduction

The price of a European option satitisfies the \textit{Black Scholes equation}

\begin{gather*}
0 = \frac{\partial f}{\partial t}(s, t) + \frac{1}{2}\sigma^2 s^2 \frac{\partial^2 f}{\partial s^2}(s, t)
+ r s \frac{\partial f}{\partial s}(s, t) - rf(s, t)
\end{gather*}
with the final condition $f(s, T) = V(s)$ where $V(s)$ is the payout.

Applying the variable change $x = log(s)$ yields
\begin{gather*}
\frac{\partial f}{\partial t}(x, t) = -\frac{1}{2}\sigma^2 \frac{\partial^2 f}{\partial x^2}(x, t)
+ (\frac{1}{2}\sigma^2 - r) \frac{\partial f}{\partial x}(x, t) + rf(x, t)
\end{gather*}

with the final condition $f(x, T) = V(x) = V(e^s)$.

A common method to solve this PDE is to use finite differences to approximate the derivatives and then
solve the equation on a discrete mesh.

## Finite difference method

We first define a mesh over space and time, usually the time is discretized such that the time step $dt$ is 1 day.
The boundaries are $0$ (today) and $T$ (the maturity of the option). The space mesh is centered to the log of the
current spot ($log(s_0)$)and the boundaries are set to $log(s_0) \pm5stddev = log(s_0) \pm 5 \sigma \sqrt{T}$.
Let's call $N$ the number of points in space and $dx$ the space step.

We use the following approximations for the derivatives:

\begin{itemize}
\item $\frac{\partial^2 f}{\partial x^2}(x_i, t_n) = \frac{f_{i+1}^n - 2 f_i^n + f_{i-1}^n}{dx^2}$
\item $\frac{\partial f}{\partial x}(x_i, t_n) = \frac{f_{i+1}^n - f_{i-1}^n}{2dx}$
\item $\frac{\partial f}{\partial t}(x_i, t_n) = \frac{f_i^{n+1} - f_i^{n}}{dt}$
\end{itemize}
where ${f_i^n = f(x_i, t_n)}$.

Let's define
\begin{gather*}L_i^n = -\frac{1}{2}\sigma^2\frac{f_{i+1}^n - 2 f_i^n + f_{i-1}^n}{dx^2} + (\frac{1}{2}\sigma^2 - r)  \frac{f_{i+1}^n - f_{i-1}^n}{2dx} + rf_i^n
\end{gather*}  the \textit{Black Scholes equation} then becomes a system of linear equations
\begin{gather*}
\frac{f_i^{n+1} - f_i^{n}}{dt} = L_i^{n+1}, i \in [1, N-1] \Longleftrightarrow
f_i^n = f_i^{n+1} - L_i^{n+1}dt, i \in [1, N-1]
\end{gather*}
Since we are solving a backward equation (given the payoff at maturity $T$, we want to compute the price of the option today), evaluating $L_i$
at $t^{n+1}$ yields an explicit scheme, i.e we can direclty compute $f_i^n$ given the price at the previous iteration $f_i^{n+1}$. While this scheme
converges fast, it is highly instable.

Another solution is to evaluate $L_i$ at $t^n$, we get
\begin{gather*}
\frac{f_i^{n+1} - f_i^{n}}{dt} = L_i^{n}, i \in [1, N-1] \Longleftrightarrow
f_i^n + L_i^n dt = f_i^{n+1}, i \in [1, N-1]
\end{gather*}
Here we need to invert a linear system to compute $f_i^n$. While this is unconditionnally stable, this is slow to converge.

To get the benefits from both schemes, the solution is to use a linear combination of them, this is called a theta scheme:
\begin{gather*}
\frac{f_i^{n+1} - f_i^{n}}{dt} = \theta L_i^n + (1-\theta) L_i^{n+1}
\end{gather*}
The closer $\theta$ is to $1$, the more stable the scheme is. The closer $\theta$ is to $0$ the faster the scheme converges. $\theta = \frac{1}{2}$ gives
the best convergence speed under unconditionnal stability and is thus usually chosen. It is known as the Crank-Nicholson scheme.

## Boundary conditions

At the boundaries of the space mesh ($i = 0$ and $i = N$) we cannot use centered finite difference
\begin{itemize}
\item $\frac{\partial^2 f}{\partial x^2}(x_0, t_n) = \frac{f_{2}^n - 2f_{1}^n + f_{0}^n}{dx^2}$
\item $\frac{\partial f}{\partial x}(x_0, t_n) = \frac{f_{1}^n - f_{0}^n}{dx}$
\item $\frac{\partial^2 f}{\partial x^2}(x_N, t_n) = \frac{f_{N}^n - 2f_{N-1}^n + f_{N-2}^n}{dx^2}$
\item $\frac{\partial f}{\partial x}(x_N, t_n) = \frac{f_{N}^n - f_{N-1}^n}{dx}$
\end{itemize}

We then need to specify values of f at the boundaries ($f_0$ and $f_N$) to be able to solve the linear system. This is called Dirichlet boundary conditions. Another possibility is to impose the derivatives at the boundaries, these are the Neumann boundary conditions.

## Work to be done

You have just joined the quantitative team of a bank, who needs to reimplement its PDE solver. Indeed, the first version was developed by a battalion of
interns who were learning C++ during their break for lunch; as a surprising result, it is highly unstable and slow (but sometimes it gives a correct price).
The villains have been punished: the interns have been fired and the manager responsible for this mess has been promoted, so at least you won't have to interact with him.

The new manager hired you for your expert skills in C++ and want you to fix the issue before mid January (or you will meet the same fate as the interns):

\begin{itemize}
\item Write the maths to get the exact expression of the linear system to solve
\item Implement the solver in C++, keeping in mind the following constraints
\begin{itemize}
\item the solver should be able to accept any kind of payoff
\item the solver must be flexible enough so the client can specify the boundary conditions
\item the solver must be flexible enough so the client can speficy different diffusion models (so $\sigma$ and $r$ might be more complicated than simple constants)
\item the client should be able to specify the mesh and the value of $\theta$
\end{itemize}
\item Test your implementation by rolling back the payoff of a call and comparing the result with the Back Scholes closed-form
\item Add methods to compute the $\delta$, $\gamma$ and $\theta$. These methods should add minimal overhead once the price is computed.
\item Add a method to compute the vega.
\end{itemize}

The source code must be well documented and the repository of the project must contain several examples and tests. In the report, you must justify your choices and clearly explain the data structure and the algorithms.