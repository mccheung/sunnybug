#coding=GBK
import XswUtility



#����Ŀ��Ŀ¼��
def GetPathName(nSvnVer=0):
    import time
    today=time.localtime()
    vStr = "%d-%d-%d_%d%d%d"%(today[0:6]) + '_svn' + str(nSvnVer)
    return vStr

#

#main
if __name__ == '__main__':
    XswUtility.FastCopy('data', 'Target', "*.pdb;*.exe")

    #ret = XswUtility.AuthNetShare(r'\\192.168.9.36\ħ��vs�����ͻ���',
    #    'jzshare', 'jzlist')
    #print(ret)
    print(GetPathName())