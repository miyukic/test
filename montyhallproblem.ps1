
function select1 {
    return (Get-Random -Maximum 3 -Minimum 0)
}

function select-sikaisya([int]$exc, [bool[]]$drs) {
    while($true) {
        $n = Get-Random -Maximum 3 -Minimum 0
        if ($n -eq $exc) {
            continue;
        }
        if ($drs[$n] -eq $true) {
            continue;
        }
        return $n
    }
}

[int]$count = 0;
[int]$times = 1000; 

1..$times | % {
    [bool[]]$doors = @($false,$false,$false);

    $doors[(Get-Random -Maximum 3 -Minimum 0)] = $true

    [int]$excep = select1
    #echo ===>$excep

    #echo ---->$(select-sikaisya $excep $doors)

    if ($doors[$excep]) {
        $count++;
    }
}

echo $($count / $times)

$count = 0;

1..$times | % {
    [bool[]]$doors = @($false,$false,$false);

    $doors[(Get-Random -Maximum 3 -Minimum 0)] = $true

    [int]$excep = select1

    [int]$sikaisya = select-sikaisya $excep $doors

    if (-not $doors[$excep]) {
        $count++;
    }
}
echo $($count / $times)
