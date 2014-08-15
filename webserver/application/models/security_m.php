<?php
class Security_m extends CI_Model{
	public function __construct(){
		parent::__construct();
	}

	public function login($user="*",$password="*"){
		$this->db->where('user_email',$user);
		$this->db->where('user_password',md5($password));

		$query = $this->db->get('users');
		if($query->num_rows() > 0){
			$this->session->set_userdata('user',$query->row());
			$sess_data = $this->session->all_userdata();
			$data = array(
			'session_id'=>$sess_data['session_id'],
			'dir_ip'=>$sess_data['ip_address'],
			'user_agent'=>$sess_data['user_agent'],
			'user_id'=>$query->row()->user_id,
			'state'=>'active',
			'entered'=>time()
			
		);
			$this->db->insert('sessions',$data);
			return true;
		}
		return false;
	}

	public function logged($user_id=null){
		$user = $this->session->userdata('user');
		
		if($user_id==null && !empty($user) ){
		  $user_id = $user->user_id;
		}
		
		$this->db->where('user_id',$user_id);
		$this->db->where('entered >',time()-86400);

		$query = $this->db->get('sessions');
		if($query->num_rows() > 0){
			return true;
		}
		return false;
	}
}
