import subprocess
import sys
import os

def do_call ( cmd_list ):
    cmd = subprocess.Popen( cmd_list, stdout=subprocess.PIPE )
    output = cmd.communicate()[0]
    assert cmd.returncode == 0, "'" + " ".join(cmd) + "' failed"
    return output

if len(sys.argv) < 2:
    print "url must be provided"
    sys.exit(1)

url_cmd = ("svn propget original_url %s"%sys.argv[1]).split()
url = do_call( url_cmd ).strip()

curr_rev_cmd = ("svn propget current_rev %s"%sys.argv[1]).split()
curr_rev = int(do_call( curr_rev_cmd))

new_rev_cmd = ['svn','info',url]
ret = do_call( new_rev_cmd )
lines = ret.split('\n')
line = lines[4]
words = line.split()
new_rev = int(words[1])

assert curr_rev <= new_rev, "sanity check"

if curr_rev < new_rev:
    diff_cmd = ['svn','diff', '--revision','%d:%d'%(curr_rev,new_rev),url]
    diff = do_call( diff_cmd )

    patch_cmd = ['patch','-p0','-d',sys.argv[1]]
    patch = subprocess.Popen( patch_cmd, stdin=subprocess.PIPE, stdout=sys.stdout )
    patch.communicate( diff )
    assert patch.returncode == 0, "'" + " ".join(patch_cmd) + "' failed"

    set_rev_cmd = ("svn propset current_rev %d %s"%(new_rev,sys.argv[1])).split()
    subprocess.check_call( set_rev_cmd )
