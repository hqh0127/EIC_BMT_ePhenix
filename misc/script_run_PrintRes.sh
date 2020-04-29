#!/bin/bash

echo ${WORK}
DETECTOR=${1}
PT=${2}
ETA=${3}

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
sed -i "s/\s\{6\}gen->set_eta_range(-\?[0-9]\+,\s[0-9]\+)\;/      gen->set_eta_range(-${ETA}, ${ETA})\;/g" Fun4All_G4_EICDetector.C
sed -i "s/gen->set_pt_range([0-9]\+\.,\s[0-9]\+\.)\;/gen->set_pt_range(${PT}., ${PT}.)\;/g" Fun4All_G4_EICDetector.C
root.exe -l -b -q "Fun4All_G4_EICDetector.C(10000)"

FNAME=G4EICDetector.root_g4tracking_eval_${DETECTOR}_eta${ETA}_`printf "%02d" ${PT}`.root

mv G4EICDetector.root_g4tracking_eval.root ${WORK}/${FNAME}

popd

root.exe -l -b -q "PrintRes.cpp(\"${FNAME}\", ${ETA}, ${PT}, \"${DETECTOR}\")"
cp ${FNAME} /work/clas12/users/qihuang/EIC_MM_momres/work/

popd
