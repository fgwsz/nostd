echo "you can input exit to abort git push."
$commit_info=Read-Host -Prompt "input commit info"
if($commit_info -eq "exit"){
    echo "git push exit!"
}else{
    git add include/*
    git add src/*
    git add CMakeLists.txt
    git add msvc_build.ps1
    git add mingw_build.ps1
    git add git_push.ps1
    $commit_info=Read-Host -Prompt "input commit info"
    git commit -m $commit_info
    git push
}
