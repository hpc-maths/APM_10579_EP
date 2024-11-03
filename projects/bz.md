---
title: "Traveling waves and spiral waves in excitable media : Belousov-Zhabotinsky"
subtitle: "APM_50179_EP project"
date: 2024-2025
---

## The mathematical model

We are concerned with the numerical approximation of some models coming from nonlinear chemical dynamics, the Belousov-Zhabotinski reaction,
a catalyzed oxidation of an organic species by acid bromate ion, for more details in illustrations, see \cite{epstein98}.
We first consider the two-variable Oregonator model, studied in \cite{jahnke89}, it has solutions that represent propagation of a steep wave front by interplay of HBrO2 (hypobromous acid) diffusion
with an autocatalytic reaction that quickly generates HBrO2 (using bromide ions $\mathrm{Br^-}$ as an intermediary species that remains always in equilibrium with local instantaneous HBrO2).
Denoting by $b=[\mathrm{HBrO_2}]$ and $c=[\mathrm{Br^-}]$, we consider the following model :

$$
\left\{
\begin{aligned}
& \partial_t b - D_b \, \Delta b = \frac{1}{\epsilon} \biggl( b(1-b) + \frac{f(q-b)c}{q+b} \biggl), \quad x \in \mathbb{R}^d, t > 0 \\
& \partial_t c - D_c \, \Delta c = b - c, \quad x \in \mathbb{R}^d, t > 0
\end{aligned}
\right.
$$ {#eq:bz2eq}

with homogenous Neumann boundary conditions, the following parameters  :
$$ \epsilon = 10^{-2}, \quad f=1.6, \quad q = 2 \times 10^{-3} $$
 the following diffusion coefficients  :
$$ \quad D_b = 2.5 \times 10^{-3}, \quad D_c = 1.5 \times 10^{-3} $$

The dynamical system associated with this system models reactive excitable media with a large time scale spectrum (see \cite{gray94} for more details). The spatial configuration with the addition of diffusion develops propagating wavefront with steep spatial gradients. Hence, this model presents all the difficulties associated with a stiff multi-scale configuration.

## Discretization and integration

### The method of lines

To solve the system ([@eq:bz2eq]), we proceed by constructing a semi-discretized problem in space to obtain a system of ordinary differential equations (method of lines).
We rely on a finite difference discretization to obtain the system of ordinary differential equations :

$$
\partial_t U = A \, U + R(U)
$$ {#eq:bz2eq_dis}

where $U(t)$ is the vector whose each component $U_i$ is written $(b_i \; c_i)^T$, $b_i$
and $c_i$ being respectively discrete approximations of $b(x_i,t)$ and $c(x_i,t)$, $A$ the matrix
representing the finite difference approximation of $D_b \, \Delta b$ and $D_c \, \Delta c$ and $R(u)$ the vector of source terms where each component can be written as follows:

$$
R_i =
\begin{bmatrix}
\displaystyle
\frac{1}{\epsilon} \biggl( b_i(1-b_i) + \frac{f(q-b_i)c_i}{q+b_i} \biggl)\\
%\displaystyle
b_i - c_i
\end{bmatrix}
$$


### Splitting method

A time operator splitting technique consists in successively solving the evolutionary problems associated with each time operator in an independent way.
For system ([@eq:bz2eq_dis]) this amounts to separately solve the two following problems:

$$
\partial_t U = A \, U \quad \text{and} \quad   \partial_t U = R(U)
$$

Strang splitting is a second order splitting method which consists in successively solving for each splitting time step $\delta t = t^{n+1}-t^n$ :

$$
\left\{
\begin{aligned}
    & {\mathrm d}_t X = R(X) & \, & \text{with $X(t^n) = U(t^n)$}                   & \,  & \text{between $t^n$ et $t^n + \delta t / 2$} \\
    & {\mathrm d}_t Y = A Y  & \, & \text{with $Y(t^n) = X(t^n+\Delta t/2)$}        & \,  & \text{between $t^n$ et $t^{n+1}$} \\
    & {\mathrm d}_t X = R(X) & \, & \text{with $X(t^n+ \delta t / 2) = Y(t^{n+1})$} & \,  & \text{between $t^n + \delta t / 2$ et $t^{n + 1}$}
\end{aligned}
\right.
$$

and finally $U(t^{n+1}) = X(t^{n+1})$.\\

This splitting scheme allows to use suitable methods for each problem (diffusion and reaction).

\subsection{The additive Runge-Kutta methods}

The order 2 and 2 stages additive Runge-Kutta method to solve the systen (\ref{eq:bz2eq}) conducts to the folowing scheme :

$$
\left\{
\begin{aligned}
& (I - \lambda \Delta t A) \, U_{1} = U^{n}, \\
& (I - \lambda \Delta t A) \, U_{2} = U^{n} + \Delta t \, R(U_1) + \Delta t \, (1-2\lambda) A \, U_1, \\
& U^{n+1} = U^{n} + \frac{\Delta t}{2} \big( R(U_1) + R(U_2) \big) + \frac{\Delta t}{2} A  \, (U_1 + U_2),
\end{aligned}
\right.
$$

$\text{with } \lambda = 1 - \displaystyle \frac{\sqrt{2}}{2}.$

A more precise method (order 2 and 3 stages) additive Runge-Kutta conducts to the following scheme :

$$
\left\{
\begin{aligned}
& U_{1} = U^{n}, \\
& (I - \lambda \Delta t A) \, U_{2} = U^{n} + \lambda dt R(Z_1), \\
& (I - \lambda \Delta t A) \, U_{3} = U^{n} + (\lambda - 1) \Delta t \, R(Z_1) + 2(1 - \lambda) \Delta t R(Z_2)\, + (1-2\lambda) \Delta t A \, U_2, \\
& U^{n+1} = U^{n} + \frac{\Delta t}{2} \big( R(U_2) + R(U_3) \big) + \frac{\Delta t}{2} A  \, (U_2 + U_3),
\end{aligned}
\right.
$$

$\text{with } \lambda = 1 - \displaystyle \frac{\sqrt{2}}{2}.$

## Work to be done

For this project, you have to

- Propose a flexible and user friendly data structure able to manage the several ODE methods.
- Manage properly each dimension.
- Manage properly the several possibilities of the right-hand side of the ODE (system of equations, space operator, ...).
- Propose a way to save the results and plot them using Python packages.
- Validate the implementation of each method for the Belousov-Zhabotinsky model.

The source code must be well documented and the repository of the project must contain several examples and tests. In the report, you must justify your choices and clearly explain the data structure and the algorithms.

\begin{thebibliography}{9}

\bibitem{epstein98}
I.R. Epstein and J.A. Pojman. \emph{An Introduction to Nonlinear Chemical Dynamics}. Oscillations, Waves, Patterns and Chaos, Oxford University Press, 1998.


\bibitem{jahnke89}
W. Jahnke, W.E. Skaggs, and A.T. Winfree. \emph{Chemical vortex dynamics in the Belousov Zhabotinsky reaction and in the two-variable Oregonator model}. J. Phys. Chem., 93 :740– 749, 1989.


\bibitem{gray94}
P. Gray and S.K. Scott. \emph{Chemical Oscillations and Instabilities}. Oxford Univ. Press, 1994.

\end{thebibliography}