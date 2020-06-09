#!/bin/bash

echo ${WORK}
DETECTOR=${1}
PT=${2}
ETA=${3}
NHIT=${4}

if [ -z "${ETA}" ]
then
    ETA=0
fi

source /work/clas12/users/qihuang/EIC_MM_momres/setup.sh

pushd "${WORK}"
if [[ ! -d "MM_EIC" ]]
then
    mkdir MM_EIC
fi
pushd MM_EIC
cp /work/clas12/users/qihuang/EIC_MM_momres/${DETECTOR}/EIC_BMT_ePhenix/*.C .
echo $PWD
sed -i "s/\s\{6\}gen->set_eta_range(-\?[0-9]\+,\s[0-9]\+)\;/      gen->set_eta_range(${ETA}, ${ETA})\;/g" Fun4All_G4_EICDetector.C
sed -i "s/gen->set_pt_range([0-9]\+\.,\s[0-9]\+\.)\;/gen->set_pt_range(${PT}., ${PT}.)\;/g" Fun4All_G4_EICDetector.C
sed -i "s/\s\{4\}example01->set_int_param(\"nhit\",\s[0-9])\;/    example01->set_int_param(\"nhit\", ${NHIT})\;/g" G4_Svtx_maps_ladders+intt_ladders+tpc_KalmanPatRec_EIC.C
root.exe -l -b -q "Fun4All_G4_EICDetector.C(10000)"

FNAME=G4EICDetector.root_g4tracking_eval_${DETECTOR}_eta${ETA}_`printf "%02d" ${PT}`_nhit${NHIT}.root

mv G4EICDetector.root_g4tracking_eval.root ${WORK}/${FNAME}

popd

root.exe -l -b -q "PrintRes.cpp(\"${FNAME}\", ${ETA}, ${PT}, \"${DETECTOR}\", \"${NHIT}\")"
cp ${FNAME} /work/clas12/users/qihuang/EIC_MM_momres/work/

popd
