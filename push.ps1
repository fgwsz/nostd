$commit_info=Read-Host -Prompt "input commit info"
if(Test-Path -Path build){
    git rm --cached build/*
}
if(Test-Path -Path out){
    git rm --cached out/*
}
git add src/*
if(Test-Path -Path include){
    git add include/*
}
git add CMakeLists.txt
git add *.ps1
git commit -m $commit_info
git push
