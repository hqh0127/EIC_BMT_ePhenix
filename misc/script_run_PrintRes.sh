#!/bin/bash

WORK="/tmp"
DETECTOR=${1}
PT=${2}
ETA=${3}

if [ -z "${ETA}" ]
then
    ETA=0
fi

source /local/home/qh261761/CEA/EIC/Singularity/setup.sh
source /cvmfs/sphenix.sdcc.bnl.gov/x8664_sl7/opt/sphenix/core/bin/setup_local.sh $HOME/CEA/EIC/EICsim/g4BMT_strip/source/build/myinstall

pushd "${WORK}"
if [[ ! -d "MM_EIC" ]]
then
    mkdir MM_EIC
fi
pushd MM_EIC
cp -r /local/home/qh261761/CEA/EIC/EICsim/MM_EIC/*.C .
sed -i "s/\s\{6\}gen->set_eta_range(-\?[0-9]\+,\s[0-9]\+)\;/      gen->set_eta_range(-${ETA}, ${ETA})\;/g" Fun4All_G4_EICDetector.C
sed -i "s/gen->set_pt_range([0-9]\+\.,\s[0-9]\+\.)\;/gen->set_pt_range(${PT}., ${PT}.)\;/g" Fun4All_G4_EICDetector.C
root.exe -l -b -q "Fun4All_G4_EICDetector.C(1000)"

FNAME=G4EICDetector.root_g4tracking_eval_eta${ETA}_`printf "%02d" ${PT}`.root

mv G4EICDetector.root_g4tracking_eval.root ${WORK}/${FNAME}

popd

root.exe -l -b -q "PrintRes.cpp(\"${FNAME}\", ${ETA}, ${PT}, \"${DETECTOR}\")"

popd
