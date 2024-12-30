# Introduzione


## Quick start 

Per compilare la su bash utilizzare il comando
```sh
g++ -Wall -Wextra main.cxx Particle.cxx ResonanceType.cxx ParticleType.cxx -pthread -std=c++17 -m64 -L/usr/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysicslMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic
```
per tutte le altre shell (come fish o zsh)
```sh
g++ -Wall -Wextra main.cxx Particle.cxx ResonanceType.cxx ParticleType.cxx -pthread -std=c++17 -m64 -L/usr/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysicslMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic
```

dopo l'esecuzione il file root viene salvato nella cartella `/output`

La macro di analisi si trova dentro `/output/analysis.C`, per eseguire lanciare il comando
```root
root [0] .x analysis.C
```
 