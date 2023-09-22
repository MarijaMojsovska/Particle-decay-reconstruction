# Particle decay reconstruction
#### (Code from the course *Object oriented programming and C++*)
&nbsp;


The data was produced by simulating the decay of two strange particles

*   two opposite charge particles in the final state, with the same mass

    $K_S^0 \\rightarrow \\pi^{+} \\pi^{-}$

*   two opposite charge particles in the final state, with different masses

    $\\Lambda^0 \\rightarrow p \\pi^{-}$

*   background events up to 10 particles, with random charges

\
**Unstable partcles**:

$K_S^0: M_K=0.497611 \\mathrm{GeV} / c^2, \\tau_K=89.54 \\mathrm{ps}$ 

$\\Lambda^0: M_{\\Lambda}=1.115683 \\mathrm{GeV} / c^2, \\tau_{\\Lambda}=263.2 \\mathrm{ps}$

Unstable particles must be reconstructed by making hypotheses on the masses of the decay products.

**Stable particles**:

$\\pi^{ \\pm}: M_\\pi=0.1395706 \\mathrm{GeV} / c^2$

$ p: M_p=0.938272 \\mathrm{GeV} / c^2\end$

Stable particles (pions, protons) cannot be distinguished.

&nbsp;

The file *particle_events.txt* contains the data
Each event contain:
*   an event identifier
*   the coordinates x, y, z of the decay point
*   the number of particles
*   for each particle 4 numbers:
    - the electric charge
    - the momentum components px , py , pz








